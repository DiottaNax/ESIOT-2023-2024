package river.monitoring.service.common;

import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;

/**
 * Represents a data point in a river monitoring system.
 */
public final class DataPoint {
    private final double waterLevel;
    private final SystemState systemState;
    private final SystemMode mode;
    private final int valveOpening;
    
    /**
     * Constructs a new DataPoint with the specified parameters.
     *
     * @param mode          the operational mode of the system.
     * @param waterLevel    the water level measurement.
     * @param valveOpening  the opening level of the valve.
     * @param systemState   the state of the system.
     */
    public DataPoint(final SystemMode mode, final double waterLevel, final int valveOpening,
                     final SystemState systemState) {
        this.systemState = systemState;
        this.mode = mode;
        this.waterLevel = waterLevel;
        this.valveOpening = valveOpening;
    }

    /**
     * Retrieves the operational mode of the system.
     *
     * @return the operational mode.
     */
    public SystemMode getMode() {
        return mode;
    }

    /**
     * Retrieves the water level measurement.
     *
     * @return the water level.
     */
    public double getWaterLevel() {
        return waterLevel;
    }

    /**
     * Retrieves the system state.
     *
     * @return the system state.
     */
    public SystemState getSystemState() {
        return systemState;
    }

    /**
     * Retrieves the opening level of the valve.
     *
     * @return the valve opening level.
     */
    public int getValveOpening() {
        return valveOpening;
    }

    /**
     * Converts the DataPoint object to a JSON representation.
     *
     * @return a JSON array containing the data point information.
     */
    public JsonArray asJson() {
        final JsonArray arr = new JsonArray();
        final JsonObject data = new JsonObject();
        data.put("MODE", this.mode.toString());
        data.put("VALVE_OPENING", this.valveOpening);
        data.put("SYSTEM_STATE", this.systemState.toString());
        data.put("FREQUENCY", this.systemState.getFrequency());
        data.put("WATER_LEVEL", this.waterLevel);
        arr.add(data);
        return arr;
    }

    @Override
    public String toString() {
        return "DataPoint [mode=" + this.mode + ", waterLevel=" + this.waterLevel + ", valveOpening="
                + this.valveOpening + ", frequency=" + this.systemState.getFrequency()
                + ", systemState=" + systemState + "]";
    }
}
