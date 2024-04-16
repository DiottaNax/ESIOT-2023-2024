package river.monitoring.service.common;

import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;

public enum SystemMode {
    AUTO("AUTO"), 
    MANUAL("MANUAL"), 
    REMOTE("REMOTE");

    final String mode;

    private SystemMode(final String mode) {
        this.mode = mode;
    }

    public JsonArray asJson() {
		final JsonArray arr = new JsonArray();
		final JsonObject data = new JsonObject();
		data.put("MODE", this.mode);
		arr.add(data);
		return arr;
	}

    @Override
    public String toString() {
        return this.mode;
    }
}
