document.addEventListener('DOMContentLoaded', (event) => {
    let oldData = new Array(); // Saves water levels
    let labels = new Array();
    let graph; // Graph for water levels

    const length = 10; // lenght of the graph (and old data)

    let bar = document.getElementById('valveOpening'); // slider for remote control
    bar.disabled = true; // the slider starts disabled until some data are collected
    let barValue = document.getElementById('valveValue');
    let remoteButton = document.getElementById('remoteButton');
    const canvas = document.getElementById('graph');
    let valveOpeningText = document.getElementById('valveOpeningText');
    let valveOpeningLevel = 0;

    const frequency = 5000; // Interval to get data in millis
    const syncRequest = setInterval(getData, frequency);

    // Convert the angle got from service into percentage
    function toPerc(angle) {
        const toPerc = 1.8;
        return Math.round(angle / toPerc);
    }

    // if a click is detected send a request to service to get remote control
    remoteButton.addEventListener('click', function() {
        let data = 'MODE_REMOTE';

        axios.post('http://localhost:8080/api/mode', data)
            .then(response => { // If remote control is set
                bar.value = valveOpeningLevel; // set bar value as the last valve opening level got from the service
                barValue.textContent = toPerc(valveOpeningLevel) + "%";
                changeMode(response.data[0].MODE); // Set new mode
            })
            .catch(error => {
            });
    });
    
    bar.addEventListener('mouseup', function() { // On bar released
        let value = bar.value; // Get setted valve opening
 
        barValue.textContent = value + '%'; // set slider label

        changeValveOpening(value); // set valve info label

        let data = {
            "VALVE_OPENING": value
        };

        //console.log(data); // DEBUG

        axios.post('http://localhost:8080/api/valve', data) // Send valve opening to service
            .then(response => {
                //console.log(response.data); // DEBUG
            })
            .catch(error => {
            });
    });

    // request data from the service
    function getData() {
        let data = {};

        axios
          .post("http://localhost:8080/api/data", data)
          .then((response) => {
            const responseData = response.data[0]; // Get json response from the service
            const timestamp = new Date().toLocaleTimeString("en-US", {
              hour12: false, // 24-hours format
            }); // Set date to show in the graph
            changeMode(responseData.MODE);
            changeSystemState(responseData.SYSTEM_STATE);
            changeWaterLevel(responseData.WATER_LEVEL, timestamp);
            changeValveOpening(responseData.VALVE_OPENING);
            valveOpeningLevel = responseData.VALVE_OPENING;
          })
          .catch((error) => {
            console.error("Error fetching data:", error);
          });
    }

    // Set component enabled/disabled, visible/unvisible and text based on the new mode set
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

    // Changes system state label (i.e. alarm level)
    function changeSystemState(newState) {
        document.getElementById('system_state').textContent = "STATE: " + newState;
    }

    // Updates graph
    function changeWaterLevel(newLevel, timestamp) {
        updateData(oldData, newLevel);
        updateData(labels, timestamp);

        // Create graph if it's null
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
        } else { // update graph's dataset if the graph is not null
            graph.data.datasets[0].data = oldData;
            graph.data.labels = labels;
            graph.update();
        }
    }

    // Update dataset adding the new water level to the array
    function updateData(data, newData) {
      data.push(newData);
      if (data.length > length) { // if array lenght is greater from the chosen graph size
        data.shift(); // drop the first item (the oldest)
      }
    }

    function changeValveOpening(newValue) {
        document.getElementById('valve_opening_value').textContent = "VALVE OPENING: " + toPerc(newValue) + "%";
    }
});
