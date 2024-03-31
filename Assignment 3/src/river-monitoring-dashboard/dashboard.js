document.addEventListener('DOMContentLoaded', (event) => {
    let currentSystemState;
    let oldData = [];
    let graph;

    let bar = document.getElementById('valveOpening');
    bar.disabled = true;
    let barValue = document.getElementById('valveValue');
    let remoteButton = document.getElementById('remoteButton');
    const canvas = document.getElementById('graph');

    const int = 5000; 
    const syncRequest = setInterval(getData, int);

    remoteButton.addEventListener('click', function() {
        let data = {
            SYSTEM_STATE: 'REMOTE'
        };
        
        axios.post('http://localhost:8080/api/data', data)
            .then(response => {
                changeState(response.data[0].SYSTEM_STATE);
            })
            .catch(error => {
                console.error('Errore:', error);
            });
    });
    
    bar.addEventListener('input', function() {
        let value = bar.value;
 
        barValue.textContent = value + '%';

        changeValveOpening(value);

        let data = {
            VALVE_OPENING: value
        };

        axios.post('http://localhost:8080/api/data', data)
            .then(response => {
                console.log(response.data);
            })
            .catch(error => {
                console.error('Errore:', error);
            });
    });
    
    function getData() {
        let data = {
        };
    
        axios.post('http://localhost:8080/api/data', data)
            .then(response => {
                changeSystemState(response.data[0].SYSTEM_STATE);
                changeAlarmLevel(response.data[0].ALARM_LEVEL);
                changeWaterLevel(response.data[0].WATER_LEVEL);
                changeValveOpening(response.data[0].VALVE_OPENING);
            })
            .catch(error => {
                console.error('Errore:', error);
            });
    }

    function changeSystemState(newState) {
        if (newState != 'REMOTE') {
            bar.disabled = true;
        } else {
            bar.disabled = false;
        }
        currentSystemState = newState;
    }

    function changeAlarmLevel(newLevel) {
        document.getElementById('alarm_level').textContent = "STATE: " + newLevel;
    }

    function changeWaterLevel(newLevel) {
        if (graph instanceof Chart) {
            console.log('sto distruggendo il grafo');
            graph.destroy();
        }

        const ctx = canvas.getContext('2d');

        console.log(typeof oldData);
        console.log(typeof newLevel);
        console.log(typeof 56);

        waterLeveltrend(oldData, newLevel);

        console.log(oldData);

        const etichette = [int, int*2, int*3, int*4, int*5, int*6];

        graph = new Chart(ctx, {
            type: 'line', 
            data: {
                labels: etichette, 
                datasets: [{
                    label: 'water level', 
                    data: oldData, 
                    backgroundColor: 'rgba(255, 99, 132, 0.2)', 
                    borderColor: 'rgba(255, 99, 132, 1)', 
                    borderWidth: 1 
                }]
            },
            options: {
                scales: {
                    yAxes: [{
                        ticks: {
                            beginAtZero: true 
                        }
                    }]
                }
            }
        });
    }

    function waterLeveltrend(oldData, newData) {
        oldData.push(newData);
        if (oldData.length > 6) {
            oldData.shift();
        }
    }

    function changeValveOpening(newValue) {
        document.getElementById('valve_opening_value').textContent = "VALVE OPENING: " + newValue + "%";
    }
});
