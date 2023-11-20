:::mermaid
flowchart 
    S((START)) -->
    CWT([CAR WAITING]) -- "movement detected" --> 
    WE([WELCOME]) -- "waited N1 secs" -->
    GO([GATE OPENING]) -- "distance <= MINDIST for N2 secs" -->
    RTW([READY TO WASH]) -- "start button pressed" -->
    CWS([CAR WASHING]) -- "N3 secs passed" -->
    WC([WASHING COMPLETED])

    CWS -- "temperature >= MAXTEMP for N4 secs" --> 
    WS([WASHING SUSPENDED]) -- "manteinance button pressed" --> CWS

    GO -- "bad movement detected" --> CWT
    WC --  "distance >= MAXDIST for N4 secs" --> CWT
:::