package river.monitoring.service.common;

import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;

/**
 * Enum representing the operational modes of a river monitoring system.
 */
public enum SystemMode {
    AUTO("AUTO"), 
    MANUAL("MANUAL"), 
    REMOTE("REMOTE");

    final String mode;

    
    private SystemMode(final String mode) {
        this.mode = mode;
    }

    /**
     * Converts the SystemMode enum to a JSON representation.
     *
     * @return a JSON array containing the mode information.
     */
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
