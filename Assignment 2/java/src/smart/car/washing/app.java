import java.util.StringTokenizer;

import serial.SerialCommChannel;
import gui.ConsoleGui;

public class app {
    
    public static void main(String[] args) throws Exception {
        SerialCommChannel channel = new SerialCommChannel("COM5",9600);		
		
        ConsoleGui gui = new ConsoleGui(channel);
        
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
