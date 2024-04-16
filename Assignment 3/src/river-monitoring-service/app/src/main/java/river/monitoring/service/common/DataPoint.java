package river.monitoring.service.common;

import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;

public final class DataPoint {
	private final double waterLevel;
	private final SystemState systemState;
	private final SystemMode mode;
	private final int valveOpening;
	
	public DataPoint(final SystemMode mode, final double waterLevel, final int valveOpening,
			final SystemState systemState) {
		this.systemState = systemState;
		this.mode = mode;
		this.waterLevel = waterLevel;
		this.valveOpening = valveOpening;
	}

	public SystemMode getMode() {
		return mode;
	}

	public double getWaterLevel() {
		return waterLevel;
	}

	public SystemState getSystemState() {
		return systemState;
	}

	public int getValveOpening() {
		return valveOpening;
	}

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
		return "DataPoint [mode=" + this.mode + "waterLevel=" + this.waterLevel + "valveOpening="
				+ this.valveOpening + ", frequency=" + this.systemState.getFrequency()
				+ ", systemState=" + systemState + "]";
	}
}
