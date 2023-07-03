package main

import (
	"bytes"
	"context"
	"flag"
	"fmt"
	"io/ioutil"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
	"time"
)

func init() {
	flag.Parse()
}

var printAllOutput = flag.Bool("print-all-output",
	false,
	"Print all output from failed and successful comands.")

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
	sokkaCFile2   = filepath.Join(sokkaDir, "out", "sokka.build"+cPhaseExt(phase(2)))
	testsDir      = filepath.Join(baseDir, "tests")
)

var (
	cmdTimeout = 10 * time.Second
)

func green(text string) string {
	return "\033[92m" + text + "\033[0m"
}

func yellow(text string) string {
	return "\033[93m" + text + "\033[0m"
}

func red(text string) string {
	return "\033[91m" + text + "\033[0m"
}

func run(name string, args ...string) error {
	var outBuffer bytes.Buffer
	ctx, cancel := context.WithTimeout(context.Background(), cmdTimeout)
	defer cancel()
	cmd := exec.CommandContext(ctx, name, args...)
	cmd.Stdout = &outBuffer
	cmd.Stderr = &outBuffer
	cmdStr := name + " " + strings.Join(args, " ")
	err := cmd.Run()
	out := outBuffer.String()
	if len(out) > 0 {
		out = strings.TrimSuffix(out, "\n")
		out = "\n" + out
	}
	if err != nil {
		return fmt.Errorf(red("FAIL")+" $ %s\n %v%s", cmdStr, err, out)
	}
	if !*printAllOutput || len(out) == 0 {
		fmt.Printf("  "+green("OK")+" $ %s\n", cmdStr)
	} else {
		fmt.Printf("  "+green("OK")+" $ %s\n%s\n", cmdStr, out)
	}
	return nil
}

func compileWithCCompiler(cFile string, p phase) (execFile string, err error) {
	execFile = strings.TrimSuffix(cFile, cExt) + execExt
	if err := run(cc, cFile, "-o", execFile); err != nil {
		return "", err
	}
	return execFile, nil
}

func compileWithBootstrapCompiler(srcFile string) (cFile, execFile string, err error) {
	const p = phase(1)
	cFile = strings.TrimSuffix(srcFile, sokkaExt) + cPhaseExt(p)
	if err := run(python, bootstrapFile, srcFile, cFile); err != nil {
		return "", "", err
	}
	execFile, err = compileWithCCompiler(cFile, p)
	if err != nil {
		return "", "", err
	}
	return cFile, execFile, nil
}

func compileWithSokkaCompiler(sokka, verb, srcDir string, p phase) (cFile, execFile string, err error) {
	outDir := srcDir + "/out"
	if err := os.MkdirAll(outDir, 0700); err != nil {
		return "", "", err
	}
	_, name := filepath.Split(srcDir)
	cFile = outDir + "/" + name + "." + verb + cPhaseExt(p)
	if err := run(sokka, verb, srcDir, cFile); err != nil {
		return "", "", err
	}
	execFile, err = compileWithCCompiler(cFile, p)
	if err != nil {
		return "", "", err
	}
	return cFile, execFile, nil
}

func main() {
	sokkaExecFile2, err := compileWithCCompiler(sokkaCFile2, phase(2))
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	success := true
	sokkaCFile3, sokkaExecFile3, err := compileWithSokkaCompiler(sokkaExecFile2, "build", sokkaDir, phase(3))
	if err != nil {
		fmt.Println(err)
		success = false
	}
	_, sokkaTestFile3, err := compileWithSokkaCompiler(sokkaExecFile2, "test", sokkaDir, phase(3))
	if err != nil {
		fmt.Println(err)
		success = false
	}
	if err := run(sokkaTestFile3); err != nil {
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
		fmt.Println(yellow("Note:") + " Sokka did not compile itself with the same output.")
		success = false
	}

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
		for p, sokkaExecFile := range [2]string{sokkaExecFile2, sokkaExecFile3} {
			for _, verb := range [2]string{"build", "test"} {
				_, execFile, err := compileWithSokkaCompiler(sokkaExecFile, verb, testDir, phase(p+2))
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
		}
	}
	if !success {
		os.Exit(1)
	}
}
