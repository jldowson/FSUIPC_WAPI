///////////////////////////////////////////////////////////////////////////////
// @File Name:     Logger.h                                                  //
// @Author:        Pankaj Choudhary                                          //
// @Version:       0.0.1                                                     //
// @L.M.D:         13th April 2015                                           //
// @Description:   For Logging into file                                     //
//                                                                           // 
// Detail Description:                                                       //
// Implemented complete logging mechanism, Supporting multiple logging type  //
// like as file based logging, console base logging etc. It also supported   //
// for different log type.                                                   //
//                                                                           //
// Thread Safe logging mechanism. Compatible with VC++ (Windows platform)   //
// as well as G++ (Linux platform)                                           //
//                                                                           //
// Supported Log Type: ERROR, ALARM, ALWAYS, INFO, BUFFER, TRACE, DEBUG      //
//                                                                           //
// No control for ERROR, ALRAM and ALWAYS messages. These type of messages   //
// should be always captured.                                                //
//                                                                           //
// BUFFER log type should be use while logging raw buffer or raw messages    //
//                                                                           //
// Having direct interface as well as C++ Singleton inface. can use          //
// whatever interface want.                                                   //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#pragma once

// C++ Header File(s)
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
// Win Socket Header File(s)
#include <Windows.h>
#include <process.h>

namespace CPlusPlusLogging
{
   // Direct Interface for logging into log file or console using MACRO(s)
   #define LOG_ERROR(x)    Logger::getInstance()->error(x)
   #define LOG_ALARM(x)	   Logger::getInstance()->alarm(x)
   #define LOG_ALWAYS(x)	Logger::getInstance()->always(x)
   #define LOG_INFO(x)     Logger::getInstance()->info(x)
   #define LOG_BUFFER(x)   Logger::getInstance()->buffer(x)
   #define LOG_TRACE(x)    Logger::getInstance()->trace(x)
   #define LOG_DEBUG(x)    Logger::getInstance()->debug(x)

   // enum for LOG_LEVEL
   typedef enum LOG_LEVEL
   {
      DISABLE_LOG       = 1,
      LOG_LEVEL_INFO	= 2,
      LOG_LEVEL_BUFFER	= 3,
      LOG_LEVEL_DEBUG   = 4,
      LOG_LEVEL_TRACE   = 5,
      ENABLE_LOG        = 6,
   }LogLevel;

   // enum for LOG_TYPE
   typedef enum LOG_TYPE
   {
      NO_LOG            = 1,
      CONSOLE           = 2,
      FILE_LOG          = 3,
      BOTH_LOG          = 4,
   }LogType;

   class Logger
   {
      public:
          static Logger* getInstance(const char* text) throw ();
          static Logger* getInstance(void (*loggerFunction)(const char* fmt)) throw ();
          static Logger* getInstance() throw ();

         // Interface for Error Log 
         void error(const char* text) throw();
         void error(std::string& text) throw();
         void error(std::ostringstream& stream) throw();

         // Interface for Alarm Log 
         void alarm(const char* text) throw();
         void alarm(std::string& text) throw();
         void alarm(std::ostringstream& stream) throw();

         // Interface for Always Log 
         void always(const char* text) throw();
         void always(std::string& text) throw();
         void always(std::ostringstream& stream) throw();

         // Interface for Buffer Log 
         void buffer(const char* text) throw();
         void buffer(std::string& text) throw();
         void buffer(std::ostringstream& stream) throw();

         // Interface for Info Log 
         void info(const char* text) throw();
         void info(std::string& text) throw();
         void info(std::ostringstream& stream) throw();

         // Interface for Trace log 
         void trace(const char* text) throw();
         void trace(std::string& text) throw();
         void trace(std::ostringstream& stream) throw();

         // Interface for Debug log 
         void debug(const char* text) throw();
         void debug(std::string& text) throw();
         void debug(std::ostringstream& stream) throw();

         // Error and Alarm log must be always enable
         // Hence, there is no interfce to control error and alarm logs

         // Interfaces to control log levels
         void updateLogLevel(LogLevel logLevel);
         void enaleLog();  // Enable all log levels
         void disableLog(); // Disable all log levels, except error and alarm

         // Interfaces to control log Types
         void updateLogType(LogType logType);
         void enableConsoleLogging();
         void enableFileLogging();
         void enableBothLogging();

         void setLoggerFunction(void (*loggerFunction)(const char* fmt));
      protected:
          Logger(const char* text);
          Logger(void (*loggerFunction)(const char* fmt));
          ~Logger();

         // Wrapper function for lock/unlock
         // For Extensible feature, lock and unlock should be in protected
         void lock();
         void unlock();

         std::string getCurrentTime();

      private:
         void logIntoFile(std::string& data);
         void logOnConsole(std::string& data);
         void operator=(const Logger& obj) {}
         bool existsFile(const std::string& baseLogFileName);

      private:
         static Logger*          m_Instance;
         std::ofstream           m_File;
         LogLevel                m_LogLevel = LOG_LEVEL_INFO;
         LogType                 m_LogType = CONSOLE;
         std::string             m_logFileName;
         void (*loggerFunction)(const char* fmt);
         CRITICAL_SECTION        m_Mutex;
   };

} // End of namespace

