package smart.car.washing;

import java.util.StringTokenizer;

import smart.car.washing.controller.Controller;
import smart.car.washing.controller.ControllerImpl;
import smart.car.washing.gui.ConsoleGui;
import smart.car.washing.serial.ChannelMonitor;

public class app {
    
    public static void main(String[] args) throws Exception {
        final ConsoleGui gui = new ConsoleGui();
        final Controller controller = new ControllerImpl(gui);
        gui.attachController(controller);
        final Thread channelMonitorThread = new Thread(new ChannelMonitor("COM9", controller));
        channelMonitorThread.start();
        
		System.out.println("Waiting Arduino for rebooting...");
		Thread.sleep(3000);
        System.out.println("Ready.");
        while (true) {
            /*try{
                String msg = channel.receiveMsg();
                System.err.println("Il messaggio ricevuto è"+ msg);
                StringTokenizer tokenizer = new StringTokenizer(msg,":");
                switch(tokenizer.nextToken()){
                    case "TEMP": 
                        gui.temp.setText("Current Temperature: "+Integer.parseInt(tokenizer.nextToken()));
                        break;
                    case "STATE":
                        gui.state.setText("Current State: "+tokenizer.nextToken());
                        break;
                    case "NUMBER":
                        gui.state.setText("Current Number: "+Integer.parseInt(tokenizer.nextToken()));
                        break;
                }
                Thread.sleep(5);
            } catch(NumberFormatException e){
                System.out.println("Non è stato possibile convertire il numero: ");
                e.printStackTrace();
            }*/
        }
    }
}
