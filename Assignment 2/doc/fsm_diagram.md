:::mermaid
flowchart 
    subgraph Controller[ControllerTask]
    direction BT
        CWT([CAR WAITING]) -- "movement detected" --> 
        WE([WELCOME]) -- "waited N1 secs" -->
        GO([GATE OPENING])
        RTW([READY TO WASH]) -- "start button pressed" -->
        CWS([CAR WASHING]) -- "N3 secs passed" -->
        WC([WASHING COMPLETED])


        WS([WASHING SUSPENDED]) -- "manteinance button pressed" --> CWS
    end

    subgraph DSTTSK[DistanceControlTask]
        ENT([ENTRANCE])
        EXT([LEAVING])
    direction TB
    end
    
    WE -- "waited N1 secs" --> ENT
    ENT -- "distance <= MINDIST for N2 secs" --> EXT & RTW
    EXT --  "distance >= MAXDIST for N4 secs" --> ENT & CWT
    WC -- "N3 secs passed" --> EXT

    subgraph TMP[TemperatureTask]
    direction LR
    end

    TMP -- "temperature >= MAXTEMP for N4 secs" --> WS

    subgraph LCD[DisplayTask]
    direction TB
    end

    subgraph BLNK[BlinkingTask]
    direction LR
        ON([ON]) --> OFF([OFF]) --> ON
    end
:::