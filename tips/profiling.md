Det finnes vanvittige mengder performance-verktøy og profilere, men her er et par rimelig
enkle og lett tilgjengelige:

# C++ (og C, Zig, Rust...)

## MacOS: sample

Åpne en terminal til å kompilere og kjøre løsningen, og en til å starte profileren:

Her hjelper det å kompilere med debug-symboler (`-g`) og gi executable et rimelig unikt navn (f.eks. `1brc-solver`).

`sample` må startes først, så det står klart til å begynne å analysere programmet med en gang det kjører.

Terminal 1:
```sh
$ sample 1brc-solver 100 1 -mayDie -wait -e
```

Terminal 2:
```sh
$ g++ -g -o 1brc-solver solution.cpp
$ ./1brc-solver
```

Etter endt kjøring (eller maks 100 sekunder) vil en teksteditor med kjøretidsanalyse bli åpnet.

## Linux: perf

Kompiler med debug-symboler (`-g`), og start programmet via `perf`:

```sh
$ g++ -g -o 1brc-solver solution.cpp
$ perf record -F 99 -B ./1brc-solver
$ perf report
```

Du vil nå få opp en konsollapplikasjon som viser hvilken del av koden som har brukt mesteparten av CPU-tiden.

# C# (og .Net generelt)

## Windows/Linux/MacOS: JetBrains dotTrace

Last ned og installer trial-versjon fra https://www.jetbrains.com/profiler/

1. "Add run configuration" type "standalone" og sett til å kjøre kompilert versjon (Release-bygg er OK) av `1brc-solver`.
2. Velg Profiling Type "Sampling"
3. Velg "Run profiling" -> "Run"

Etter endt kjøring skal du få opp et nytt vindu med analyse av kjøretid.

