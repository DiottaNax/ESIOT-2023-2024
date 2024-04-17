document.addEventListener('DOMContentLoaded', (event) => {
    let oldData = new Array();
    let labels = new Array();
    let graph;

    const length = 10;

    let bar = document.getElementById('valveOpening');
    bar.disabled = true;
    let barValue = document.getElementById('valveValue');
    let remoteButton = document.getElementById('remoteButton');
    const canvas = document.getElementById('graph');
    let valveOpeningText = document.getElementById('valveOpeningText');

    const int = 5000; 
    const syncRequest = setInterval(getData, int);

    remoteButton.addEventListener('click', function() {
        let data = 'MODE_REMOTE';
        
        axios.post('http://localhost:8080/api/mode', data)
            .then(response => {
                changeMode(response.data[0].MODE);
            })
            .catch(error => {
            });
    });
    
    bar.addEventListener('change', function() {
        let value = bar.value;
 
        barValue.textContent = value + '%';

        changeValveOpening(value);

        let data = {
            "VALVE_OPENING": value
        };

        console.log(data);

        axios.post('http://localhost:8080/api/valve', data)
            .then(response => {
                console.log(response.data);
            })
            .catch(error => {
            });
    });
    
    function getData() {
        let data = {};

        axios
          .post("http://localhost:8080/api/data", data)
          .then((response) => {
            const responseData = response.data[0];
            const timestamp = new Date().toLocaleTimeString("en-US", {
              hour12: false,
            }); // Use 24-hour format for clarity

            changeMode(responseData.MODE);
            changeSystemState(responseData.SYSTEM_STATE);
            changeWaterLevel(responseData.WATER_LEVEL, timestamp);
            changeValveOpening(responseData.VALVE_OPENING);
          })
          .catch((error) => {
            console.error("Error fetching data:", error);
          });
    }

    function changeMode(newMode) {
        if (newMode == 'REMOTE') {
            bar.disabled = false;
            bar.style.display = 'block';
            valveOpeningText.style.display = 'block';
            valveValue.style.display = 'block';
            remoteButton.textContent = "Auto Control"
        } else if (newMode == 'MANUAL') {
            bar.style.display = 'none';
            bar.disabled = true;
            valveOpeningText.style.display = 'none';
            valveValue.style.display = 'none';
            remoteButton.disabled = true;
            remoteButton.textContent = "Remote Control"
        } else {
            bar.style.display = 'none';
            bar.disabled = true;
            valveOpeningText.style.display = 'none';
            valveValue.style.display = 'none';
            remoteButton.disabled = false;
            remoteButton.textContent = "Remote Control"
        }
    }

    function changeSystemState(newState) {
        document.getElementById('system_state').textContent = "STATE: " + newState;
    }

    function changeWaterLevel(newLevel, timestamp) {
        updateData(oldData, newLevel);
        updateData(labels, timestamp);

        if (!graph) {
            const ctx = canvas.getContext("2d");

            graph = new Chart(ctx, {
            type: "line",
            data: {
                labels,
                datasets: [
                {
                    label: "water level",
                    data: [...oldData],
                    backgroundColor: "rgba(255, 99, 132, 0.2)",
                    borderColor: "rgba(255, 99, 132, 1)",
                    borderWidth: 2,
                },
                ],
            },
            options: {
                // Optional: Customize x-axis formatting (consider library like moment.js)
                scales: {
                xAxes: [
                    {
                    type: "time",
                    time: {
                        // Adjust time display format as needed (e.g., 'HH:mm:ss')
                        unit: "minute",
                        displayFormats: {
                        minute: "HH:mm",
                        },
                    },
                    },
                ],
                },
            },
            });
        } else {
            graph.data.datasets[0].data = oldData;
            graph.data.labels = labels;
            graph.update();
        }
    }

    function updateData(data, newData) {
      data.push(newData);
      if (data.length > length) {
        data.shift();
      }
    }

    function changeValveOpening(newValue) {
        document.getElementById('valve_opening_value').textContent = "VALVE OPENING: " + newValue + "%";
    }
});
