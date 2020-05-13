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
make        # Compile all dependencies (including GraphViewer)
make clean  # Cleanup all files (except GraphViewer)
make test   # Run unit tests
```

## Running

### View

```
./main view FRACTION FLAGS

FRACTION    Fraction of nodes to draw (improves display performance).
FLAGS       Flag which roads to draw (add them to combine):

            ┏━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━┳━━━━━━━┓
            ┃ Type of road  ┃ Description   ┃ Flag  ┃
            ┡━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━╇━━━━━━━┩
            │ Motorway      │ Red           │     1 │
            │ Trunk         │ Pink          │     2 │
            │ Primary       │ Orange        │     4 │
            │ Secondary     │ Yellow        │     8 │
            │ Tertiary      │ Gray          │    16 │
            │ Road          │ Gray          │    32 │
            │ Residential   │ Gray          │    64 │
            │ Slow          │ Gray, dashed  │   128 │
            └───────────────┴───────────────┴───────┘
```

#### Examples

- To see all types of roads with a fraction of 5, run `./main view 5 255`
- To see all main roads with a fraction of 3, run `./main view 3 15`

### Speed

```
./main speed FRACTION FLAGS

FRACTION    Fraction of nodes to draw (improves display performance).
FLAGS       Flag which roads to draw (add them to combine):

            ┏━━━━━━━━━━━━━━━┳━━━━━━━┓
            ┃ Type of road  ┃ Flag  ┃
            ┡━━━━━━━━━━━━━━━╇━━━━━━━┩
            │ Motorway      │     1 │
            │ Trunk         │     2 │
            │ Primary       │     4 │
            │ Secondary     │     8 │
            │ Tertiary      │    16 │
            │ Road          │    32 │
            │ Residential   │    64 │
            │ Slow          │   128 │
            └───────────────┴───────┘

Roads are coloured according to the following table:
┏━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━┓
┃ Speed [km/h] (up to)  ┃ Colour  ┃
┡━━━━━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━┩
│                   120 │ Red     │
│                   100 │ Orange  │
│                    80 │ Yellow  │
│                    60 │ Green   │
│                    50 │ Black   │
│                    40 │ Gray    │
└───────────────────────┴─────────┘
```

### Strongly connected components

```
./main scc FRACTION FLAGS

FRACTION    Fraction of nodes to draw (improves display performance).
FLAGS       Flag which roads to draw (add them to combine):

            ┏━━━━━━━━━━━━━━━┳━━━━━━━┓
            ┃ Type of road  ┃ Flag  ┃
            ┡━━━━━━━━━━━━━━━╇━━━━━━━┩
            │ Motorway      │     1 │
            │ Trunk         │     2 │
            │ Primary       │     4 │
            │ Secondary     │     8 │
            │ Tertiary      │    16 │
            │ Road          │    32 │
            │ Residential   │    64 │
            │ Slow          │   128 │
            └───────────────┴───────┘

Roads are coloured red if they connect two nodes in the train station's SCC, or gray otherwise.
```
Nortada: 286968787
Unicer: 7186948192
