package river.monitoring.service.api;

/**
 * This interface defines an observer for a communication channel.

 * <p>An observer is an object that is notified whenever a new message arrives
 * on the channel. The observer implements the {@link #notifyNewMessage()} method,
 * which is called with the received message as an argument.</p>

 * @param <Message> The type of message that can be received on the channel.
 */
public interface ChannelObserver<Message> {

  /**
   * This method is called whenever a new message arrives on the channel.

   * @param message The message received on the channel.
   */
  void notifyNewMessage(Message message);
}
