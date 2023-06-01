package main

import (
	"bytes"
	"fmt"
	"io/ioutil"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
)

const (
	sokkaExt = ".sk"
	cExt     = ".c"
	execExt  = ""
)

type phase int

func phaseExt(p phase) string {
	return fmt.Sprintf(".%03d", p)
}

func cPhaseExt(p phase) string {
	return phaseExt(p) + cExt
}

func execPhaseExt(p phase) string {
	return phaseExt(p) + execExt
}

const (
	python = "python3"
	cc     = "gcc"
)

var (
	baseDir       = "."
	bootstrapDir  = filepath.Join(baseDir, "bootstrapping")
	bootstrapFile = filepath.Join(bootstrapDir, "sokka.py")
	sokkaDir      = filepath.Join(baseDir, "sokka")
	sokkaFile     = filepath.Join(sokkaDir, "sokka.sk")
	testsDir      = filepath.Join(baseDir, "tests")
)

func run(name string, args ...string) error {
	var outBuffer bytes.Buffer
	cmd := exec.Command(name, args...)
	cmd.Stdout = &outBuffer
	cmd.Stderr = &outBuffer
	cmdStr := name + " " + strings.Join(args, " ")
	err := cmd.Run()
	if err != nil {
		out := outBuffer.String()
		if len(out) > 0 {
			out = "\n" + out
		}
		return fmt.Errorf("FAIL $ %s\n %v%s", cmdStr, err, out)
	}
	fmt.Printf("  OK $ %s\n", cmdStr)
	return nil
}

func compileWithBootstrapCompiler(srcFile string) (cFile, execFile string, err error) {
	const p = phase(1)
	cFile = strings.TrimSuffix(srcFile, sokkaExt) + cPhaseExt(p)
	if err := run(python, bootstrapFile, srcFile, cFile); err != nil {
		return "", "", err
	}
	execFile = strings.TrimSuffix(srcFile, sokkaExt) + execPhaseExt(p)
	if err := run(cc, cFile, "-o", execFile); err != nil {
		return "", "", err
	}
	return cFile, execFile, nil
}

func compileWithSokkaCompiler(sokka, srcFile string, p phase) (cFile, execFile string, err error) {
	cFile = strings.TrimSuffix(srcFile, sokkaExt) + cPhaseExt(p)
	if err := run(sokka, srcFile, cFile); err != nil {
		return "", "", err
	}
	execFile = strings.TrimSuffix(srcFile, sokkaExt) + execPhaseExt(p)
	if err := run(cc, cFile, "-o", execFile); err != nil {
		return "", "", err
	}
	return cFile, execFile, nil
}

func main() {
	success := true
	entries, err := ioutil.ReadDir(testsDir)
	if err != nil {
		fmt.Printf("failed to read test dir: %v\n", err)
		os.Exit(1)
	}
	for _, dir := range entries {
		if !dir.IsDir() {
			continue
		}
		testDir := filepath.Join(testsDir, dir.Name())
		testFile := filepath.Join(testDir, dir.Name()+".sk")
		_, execFile, err := compileWithBootstrapCompiler(testFile)
		if err != nil {
			fmt.Println(err)
			success = false
			continue
		}
		if err := run(execFile); err != nil {
			fmt.Println(err)
			success = false
			continue
		}
	}
	_, sokkaExecFile1, err := compileWithBootstrapCompiler(sokkaFile)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	sokkaCFile2, sokkaExecFile2, err := compileWithSokkaCompiler(sokkaExecFile1, sokkaFile, phase(2))
	if err != nil {
		fmt.Println(err)
		success = false
	} else {
		sokkaCFile3, _, err := compileWithSokkaCompiler(sokkaExecFile2, sokkaFile, phase(3))
		if err != nil {
			fmt.Println(err)
			success = false
		}
		sokkaCFile2Contents, err := ioutil.ReadFile(sokkaCFile2)
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}
		sokkaCFile3Contents, err := ioutil.ReadFile(sokkaCFile3)
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}
		if !bytes.Equal(sokkaCFile2Contents, sokkaCFile3Contents) {
			fmt.Println("Sokka did not compile itself with the same output.")
		}
	}

	for _, dir := range entries {
		if !dir.IsDir() {
			continue
		}
		testDir := filepath.Join(testsDir, dir.Name())
		testFile := filepath.Join(testDir, dir.Name()+".sk")
		_, execFile, err := compileWithSokkaCompiler(sokkaExecFile1, testFile, phase(2))
		if err != nil {
			fmt.Println(err)
			success = false
			continue
		}
		if err := run(execFile); err != nil {
			fmt.Println(err)
			success = false
			continue
		}
	}
	if !success {
		os.Exit(1)
	}
}
