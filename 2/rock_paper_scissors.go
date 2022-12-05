package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"os"
	"strings"
)

func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		log.Fatal(err)	
	}
	defer file.Close()

	// fmt.Println(handle_input(strings.NewReader("A Y\nB X\nC Z")))
	fmt.Println(handle_input(file))
}

func handle_input(input io.Reader) uint {
	sum := uint(0)
	selection_points := map[string]uint{"X":1, "Y":2, "Z":3}
	outcome_points := map[string]map[string]uint{
		"A":{"X":3,"Y":6,"Z":0},
		"B":{"X":0,"Y":3,"Z":6},
		"C":{"X":6,"Y":0,"Z":3},
	}
	scanner := bufio.NewScanner(input)
	scanner.Split(bufio.ScanLines)
	for scanner.Scan() {
		round := strings.Split(scanner.Text(), " ")
		sum += selection_points[round[1]] + outcome_points[round[0]][round[1]]
	}
	return sum
}
