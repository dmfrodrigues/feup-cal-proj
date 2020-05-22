# PortoCityTransfers <!-- {#mainpage} -->

![Compile reports](https://github.com/dmfrodrigues/feup-cal-proj/workflows/Compile%20reports/badge.svg)

![Test](https://github.com/dmfrodrigues/feup-cal-proj/workflows/Test/badge.svg)

- **Project name:** PortoCityTransfers
- **Short description:** Console-based program to manage a shuttle company
- **Environment:** Unix/Windows console
- **Tools:** C++
- **Institution:** [FEUP](https://sigarra.up.pt/feup/en/web_page.Inicial)
- **Course:** [CAL](https://sigarra.up.pt/feup/en/UCURR_GERAL.FICHA_UC_VIEW?pv_ocorrencia_id=436441) (Algorithm Design and Analysis)
<!-- - **Project grade:** ??/20.0 -->
- **Group members:**
    - Diogo Miguel Ferreira Rodrigues (dmfrodrigues2000@gmail.com / diogo.rodrigues@fe.up.pt)
    - João António Cardoso Vieira e Basto de Sousa (up201806613@fe.up.pt)
    - Rafael Soares Ribeiro (up201806330@fe.up.pt)

## Media

## Installing

If you are cloning from GitHub, you should pull all LFS files with

```sh
git lfs fetch --all
```

and pull all submodules with

```sh
git submodule update --init --recursive # If for the first time
```

### Make commands

```sh
make            # Compile all dependencies and libraries
make clean      # Cleanup files (except submodules and map/)
make cleanall   # Cleanup all files
make test       # Run unit tests
```

## Running

### Interesting locations

You can use some of these locations to explore most functionalities of this program:

| Location                      | Municipality      | Node number   |
|-------------------------------|-------------------|---------------|
| Monte Crasto                  | Gondomar          | 2454698517    |
| Casa Branca de Gramido        | Gondomar          | 1551005098    |
| Maia city hall                | Maia              | 5272120014    |
| Porto Airport                 | Maia              | 4102094652    |
| SONAE                         | Maia              | 5702537845    |
| Zoo Maia                      | Maia              | 4551001973    |
| EXPONOR                       | Matosinhos        | 1436599811    |
| Fábrica Unicer                | Matosinhos        | 7186948192    |
| NorteShopping                 | Matosinhos        | 4606348154    |
| Port of Leixões               | Matosinhos        | 4612166056    |
| Fábrica Nortada               | Porto             | 286968787     |
| FCUP                          | Porto             | 128672575     |
| FEUP                          | Porto             | 4523960191    |
| Palácio de Cristal            | Porto             | 3391598673    |
| São João Baptista Fortress    | Porto             | 4567051363    |
| Serra de Santa Justa          | Valongo           | 6426059706    |
| Afurada marina                | Vila Nova de Gaia | 1143316550    |
| Monastery of Serra do Pilar   | Vila Nova de Gaia | 3398946056    |
| Sandeman                      | Vila Nova de Gaia | 1143316550    |
| Senhor da Pedra beach         | Vila Nova de Gaia | 4764305642    |
| Zoo Santo Inácio              | Vila Nova de Gaia | 1324797708    |

### Graphical uses

For all graphical uses, `FLAGS` flags which roads to draw (add them to combine):

| Type of road  | Description   | Flag  |
|---------------|---------------|-------|
| Motorway      | Red           |     1 |
| Trunk         | Pink          |     2 |
| Primary       | Orange        |     4 |
| Secondary     | Yellow        |     8 |
| Tertiary      | Gray          |    16 |
| Road          | Gray          |    32 |
| Residential   | Gray          |    64 |
| Slow          | Gray, dashed  |   128 |

#### View

```
./main view FRACTION FLAGS

FRACTION    Fraction of nodes to draw (improves display performance).
FLAGS       Flag which roads to draw (add them to combine).
```

#### Examples

- To see all types of roads with a fraction of 5, run `./main view 5 255`
- To see all main roads with a fraction of 3, run `./main view 3 15`

### Speed

```
./main speed FRACTION FLAGS

FRACTION    Fraction of nodes to draw (improves display performance).
FLAGS       Flag which roads to draw (add them to combine).
```

Roads are coloured according to the following table:
| Speed [km/h] (up to)  | Colour  |
|-----------------------|---------|
|                   120 | Red     |
|                   100 | Orange  |
|                    80 | Yellow  |
|                    60 | Green   |
|                    50 | Black   |
|                    40 | Gray    |

### Strongly connected components

```
./main scc FRACTION FLAGS

FRACTION    Fraction of nodes to draw (improves display performance).
FLAGS       Flag which roads to draw (add them to combine).
```

Roads are coloured red if they connect two nodes in the train station's SCC, or gray otherwise.

### Shortest path

```
./main scc FRACTION FLAGS SOUR DEST [-v]
./main scc FRACTION FLAGS SOUR_LAT SOUR_LON DEST_LAT DEST_LON [-v]

FRACTION    Fraction of nodes to draw (improves display performance).
FLAGS       Flag which roads to draw (add them to combine).
SOUR        Source node (beginning) of the path we are looking for.
SOUR_LAT    Latitude of the source coordinate.
SOUR_LON    Longitude of the source coordinate.
DEST        Destination (end) of the path we are looking for.
DEST_LAT    Latitude of the destination coordinate.
DEST_LON    Longitude of the destination coordinate.
-v          Colour visited nodes according to the algorithms that explored them.
```

You can use either `./main scc FRACTION FLAGS SOUR DEST [-v]` or `./main scc FRACTION FLAGS SOUR_LAT SOUR_LON DEST_LAT DEST_LON [-v]`, where the second option is similar to the first, with only the extra step of finding, for the source and destination coordinates, the closest nodes of the graph that are connected to the train station.

Roads are coloured according to the following table:

| Algorithm                            | Path colour | Visited nodes colour |
|--------------------------------------|-------------|----------------------|
| Dijkstra's algorithm with early stop | Black       | Pink                 |
| A* algorithm, 90km/h                 | Black       | Red                  |
| A* algorithm, 60km/h                 | Magenta     | Magenta              |
| A* algorithm, 30km/h                 | Blue        | Blue                 |
| A* algorithm, 10km/h                 | Cyan        | Cyan                 |

#### Examples

- To get paths between FEUP and FCUP, you can run either of
```sh
./main path 1 255 4523960191 128672575
./main path 1 255 41.1777 -8.598 41.1522 -8.6361
```