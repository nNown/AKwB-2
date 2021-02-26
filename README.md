# Line to original graph conversion
Application takes path to graph in particular format and check whether is it line graph, if so is it linear and transforms it into its original graph.
Useful in simplification of Hamiltonian path/cycle search problem. By using original graph of line graph it is possible to find it by obtaining eulerian path/cycle.

## Parameters

| Parameter                           | Data type |
|-------------------------------------|-----------|
| Paths to saved graphs (paths...)    | String    | 

### Installation

```bash
make
```

### Usage
```bash
./main paths...
```