package smart.car.washing.gui;

import smart.car.washing.controller.Controller;

public interface Dashboard {

    void attachController(final Controller controller);

    void updateState(final String state);

    void updateWashingNumber(final int number);

    void updateTemperature(final int temperature);
}
