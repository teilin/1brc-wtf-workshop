using System.Collections.Generic;
using System;
using System.Diagnostics;
using System.IO;

class StationData
{
    public float Minimum;
    public float Maximum;
    public float Sum;
    public int Count;
    public StationData()
    {
        Minimum = float.MaxValue;
        Maximum = float.MinValue;
        Sum = 0;
        Count = 0;
    }
}

public class Calculate
{
    public static void Main(string[] args)
    {
        string inputFile;
        if (args.Length > 0)
        {
            inputFile = args[0];
        }
        else
        {
            inputFile = "../sample.txt";
            Console.Error.WriteLine("No input file given, using default");
        }
        Console.Error.WriteLine($"Reading file {inputFile}");
        var stopwatch = Stopwatch.StartNew();
        IEnumerable<string> lines = File.ReadLines(inputFile);
        var results = ParseLines(lines);
        stopwatch.Stop();
        Output(results, stopwatch.Elapsed);
    }

    private static Dictionary<string, StationData> ParseLines(IEnumerable<string> lines)
    {
        var results = new Dictionary<string, StationData>();
        foreach (var line in lines)
        {
            var lineParts = line.Split(";");
            var stationName = lineParts[0];
            var temperature = float.Parse(lineParts[1]);
            StationData stationData = results.GetValueOrDefault(stationName, new StationData());
            stationData.Minimum = Math.Min(stationData.Minimum, temperature);
            stationData.Maximum = Math.Max(stationData.Maximum, temperature);
            stationData.Sum += temperature;
            stationData.Count += 1;
            results[stationName] = stationData;
        }
        return results;
    }

    private static void Output(Dictionary<string, StationData> results, TimeSpan elapsed)
    {
        var measurementsCount = 0;
        foreach (var entry in results)
        {
            measurementsCount += entry.Value.Count;
            Console.WriteLine(string.Format("{0};{1:F1};{2:F1};{3:F1}",
                            entry.Key,
                            entry.Value.Minimum,
                            entry.Value.Sum / entry.Value.Count,
                            entry.Value.Maximum));
        }
        Console.Error.WriteLine(string.Format("Read {0} measurements in {1}m{2}.{3:D3}s",
                measurementsCount,
                elapsed.Minutes,
                elapsed.Seconds,
                elapsed.Milliseconds));
    }
}
