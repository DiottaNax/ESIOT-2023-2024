#ifndef __MSGSERVICE__
#define __MSGSERVICE__

#include "Arduino.h"

/**
 * @brief Represents a message with content.
 *
 * This class encapsulates a message with content.
 */
class Msg {
public:
  /**
   * @brief Constructor for Msg class.
   *
   * Initializes the message with the specified content.
   *
   * @param content The content of the message.
   */
  Msg(String content){
    this->content = content;
  }
  /**
   * @brief Get the content of the message.
   *
   * @return The content of the message as a String.
   */
  String getContent(){
    return content;
  }
private:
  String content; //The content of a message.
};

/**
 * @brief Abstract base class for message matching patterns.
 *
 * This class defines the interface for message matching patterns.
 */
class Pattern {
public:
  /**
   * @brief Pure virtual function to match a message.
   *
   * @param m The message to match against.
   * @return True if the message matches the pattern, false otherwise.
   */
  virtual boolean match(const Msg& m) = 0;  
};

/**
 * @brief Service class for handling messages.
 *
 * The MsgService class provides methods to send, receive, and check the
 * availability of messages. 
 */
class MsgServiceClass {
public:
  Msg* currentMsg; //Pointer to the currently received message.
  bool msgAvailable; //Flag indicating whether a message is available.
  /**
   * @brief Initialize the MsgService.
   */
  void init();  
  /**
   * @brief Check if a message is available.
   *
   * @return True if a message is available, false otherwise.
   */
  bool isMsgAvailable();
  /**
   * @brief Receive the next available message.
   *
   * @return Pointer to the received message.
   */
  Msg* receiveMsg();
  /**
   * @brief Check if a message matching the specified pattern is available.
   *
   * @param pattern The pattern to match against.
   * @return True if a matching message is available, false otherwise.
   */
  bool isMsgAvailable(Pattern& pattern);
  /**
   * @brief Receive the next available message matching the specified pattern.
   *
   * @param pattern The pattern to match against.
   * @return Pointer to the received message.
   */
  Msg* receiveMsg(Pattern& pattern);
  /**
   * @brief Send a message.
   *
   * @param msg The message to send.
   */
  void sendMsg(Msg& msg);
  /**
   * @brief Send a message with the specified content.
   *
   * @param msg The content of the message to send.
   */
  void sendMsg(const String& msg);
};

/**
 * @brief Instance of the MsgServiceClass for external use.
 */
extern MsgServiceClass MsgService;

#endif
