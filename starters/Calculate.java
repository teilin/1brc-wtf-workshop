import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class Calculate {
    static record StationData(
            float minimum,
            float maximum,
            float sum,
            int count) {
    }

    public static void main(String[] args) throws IOException {
        String inputFile;
        if (args.length > 0) {
            inputFile = args[0];
        } else {
            inputFile = "../sample.txt";
            System.err.println("No input file given, using default");
        }
        System.err.println(String.format("Reading file %s", inputFile));
        var start = System.currentTimeMillis();
        var reader = new BufferedReader(new FileReader(inputFile));
        var results = parseLines(reader);
        reader.close();
        var end = System.currentTimeMillis();
        output(results, end - start);
    }

    private static Map<String, StationData> parseLines(BufferedReader reader) throws IOException {
        Map<String, StationData> results = new HashMap<>();
        while (true) {
            var line = reader.readLine();
            if (line == null)
                break;
            var lineParts = line.split(";");
            var stationName = lineParts[0];
            var temperature = Float.parseFloat(lineParts[1]);
            StationData stationData = results.computeIfAbsent(
                    stationName,
                    (key) -> new StationData(Float.MAX_VALUE, Float.MIN_VALUE, 0, 0));
            results.put(stationName,
                    new StationData(
                            Math.min(stationData.minimum, temperature),
                            Math.max(stationData.maximum, temperature),
                            stationData.sum + temperature,
                            stationData.count + 1));
        }
        return results;
    }

    private static void output(Map<String, StationData> results, long timeMs) {
        var measurementsCount = 0;
        for (var entry : results.entrySet()) {
            measurementsCount += entry.getValue().count;
            System.out.println(
                    String.format("%s;%.1f;%.1f;%.1f",
                            entry.getKey(),
                            entry.getValue().minimum,
                            entry.getValue().sum / entry.getValue().count,
                            entry.getValue().maximum));
        }
        System.err.println(String.format("Read %d measurements in %dm%.2fs",
                measurementsCount,
                timeMs / 60_000,
                (float) (timeMs % 60_000) / 1_000));
    }
}
