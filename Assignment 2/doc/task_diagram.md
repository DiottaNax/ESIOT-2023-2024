:::mermaid
flowchart

    subgraph DistanceTask[DistanceControlTask]
        ENT([ENTRANCE]) --> EXT([LEAVING])
        EXT --> ENT
    direction TB
    end

    subgraph TMP[TemperatureTask]
    direction LR
    end

    subgraph LCD[DisplayTask]
    direction TB
    end

    subgraph Controller[ControllerTask]
        direction TB
            CWT([CAR WAITING])
            WE([WELCOME])
            GO([GATE OPENING])
            WC([WASHING COMPLETED])
            RTW([READY TO WASH])
            CWS([CAR WASHING])
            WS([WASHING SUSPENDED])
    end

    DistanceTask -. DEACTIVATE ..-> DistanceTask
    WC -. ACTIVATE .-> DistanceTask

    WE -. ACTIVATE .-> LCD
    WC -. DEACTIVATE .-> LCD
    GO -. ACTIVATE .-> DistanceTask

    subgraph BLNK[BlinkingTask]
    direction LR
        ON([ON]) --> OFF([OFF]) --> ON
    end

    GO -. ACTIVATE .-> BLNK
    RTW -. DEACTIVATE .-> BLNK
    CWS -. ACTIVATE .-> BLNK
    WC -. DEACTIVATE .-> BLNK

    CWS -. ACTIVATE .-> TMP
    WC -. DEACTIVATE .-> TMP

:::