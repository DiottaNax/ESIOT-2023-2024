document.addEventListener('DOMContentLoaded', (event) => {
    let oldData = new Array();
    let graph;

    let bar = document.getElementById('valveOpening');
    bar.disabled = true;
    let barValue = document.getElementById('valveValue');
    let remoteButton = document.getElementById('remoteButton');
    const canvas = document.getElementById('graph');

    const int = 5000; 
    const syncRequest = setInterval(getData, int);

    remoteButton.addEventListener('click', function() {
        let data = '';
        
        axios.post('http://localhost:8080/api/mode', data)
            .then(response => {
                changeSystemState(response.data[0].MODE);
            })
            .catch(error => {
            });
    });
    
    bar.addEventListener('input', function() {
        let value = bar.value;
 
        barValue.textContent = value + '%';

        changeValveOpening(value);

        let data = {
            VALVE_OPENING: value
        };

        axios.post('http://localhost:8080/api/valve', data)
            .then(response => {
                console.log(response.data);
            })
            .catch(error => {
            });
    });
    
    function getData() {
        let data = {
        };
    
        axios.post('http://localhost:8080/api/data', data)
            .then(response => {
                changeMode(response.data[0].MODE);
                changeSystemState(response.data[0].SYSTEM_STATE);
                changeWaterLevel(response.data[0].WATER_LEVEL);
                changeValveOpening(response.data[0].VALVE_OPENING);
            })
            .catch(error => {
            });
    }

    function changeMode(newMode) {
        if (newMode == 'REMOTE') {
            bar.disabled = false;
        } else if (newMode == 'MANUAL') {
            bar.disabled = true;
            remoteButton.disabled = true;
        } else {
            bar.disabled = true;
            remoteButton.disabled = false;
        }
    }

    function changeSystemState(newState) {
        document.getElementById('system_state').textContent = "STATE: " + newState;
    }

    function changeWaterLevel(newLevel) {
        if (graph instanceof Chart) {
            graph.destroy();
        }

        const ctx = canvas.getContext('2d');

        waterLeveltrend(oldData, newLevel);

        console.log(oldData);

        const etichette = [int, int*2, int*3, int*4, int*5, int*6];

        graph = new Chart(ctx, {
            type: 'line', 
            data: {
                labels: etichette, 
                datasets: [{
                    label: 'water level', 
                    data: [...oldData], 
                    backgroundColor: 'rgba(255, 99, 132, 0.2)', 
                    borderColor: 'rgba(255, 99, 132, 1)', 
                    borderWidth: 2 
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
        oldData.push(parseFloat(newData));
        if (oldData.length > 6) {
            oldData.shift();
        }
    }

    function changeValveOpening(newValue) {
        document.getElementById('valve_opening_value').textContent = "VALVE OPENING: " + newValue + "%";
    }
});
