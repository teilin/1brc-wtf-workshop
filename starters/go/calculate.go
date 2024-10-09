package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
	"time"
)

type StationData struct {
	minimum float64
	maximum float64
	sum     float64
	count   int
}

func main() {
	inputFile := "measurements.txt"
	if len(os.Args) > 1 {
		inputFile = os.Args[1]
	}
	fmt.Fprintln(os.Stderr, "Reading records from", inputFile)

	file, err := os.Open(inputFile)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	start := time.Now()
	countLines := 0
	results, err := parseLines(file)
	if err != nil {
		panic(err)
	}
	for k, v := range results {
		countLines += v.count
		fmt.Printf("%s;%.1f;%.1f;%.1f\n", k, v.minimum, v.sum/float64(v.count), v.maximum)
	}
	duration := time.Now().Sub(start)
	fmt.Fprintf(os.Stderr, "Read %d measurements in %s\n", countLines, duration.Abs().Truncate(time.Millisecond))
}

func parseLines(file *os.File) (map[string]StationData, error) {
	results := make(map[string]StationData)
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		split := strings.Split(line, ";")
		stationName := split[0]
		measurement, err := strconv.ParseFloat(split[1], 64)
		if err != nil {
			return nil, err
		}
		if entry, found := results[stationName]; found {
			results[stationName] = StationData{
				maximum: max(entry.maximum, measurement),
				minimum: min(entry.minimum, measurement),
				sum:     entry.sum + measurement,
				count:   entry.count + 1,
			}
		} else {
			results[stationName] = StationData{
				maximum: measurement,
				minimum: measurement,
				sum:     measurement,
				count:   1,
			}
		}
	}
	return results, scanner.Err()
}
