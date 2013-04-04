/*
 * Copyright (C) 2011 Alexandre Quessy
 *
 * This file is part of Tempi.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software ither version 3 of the License, or
 * (at your option) any later version.
 * 
 * Tempi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with Tempi.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * Logging utilities
 */

#ifndef __ENTITY_LOGGER_H__
#define __ENTITY_LOGGER_H__

#include <sstream> // to provide std::ostringstream
#include <tr1/memory>

namespace entity {

/**
 * Log level
 */
typedef enum
{
    DEBUG = 700, // log4cpp::Priority::DEBUG,
    INFO = 600, // log4cpp::Priority::INFO,
    NOTICE = 500, // log4cpp::Priority::NOTICE,
    WARNING = 400, // log4cpp::Priority::WARN,
    ERROR = 300, //log4cpp::Priority::ERROR
    CRITICAL = 200 // log4cpp::Priority::CRIT,
} LogLevel;

struct LoggerPrivate; // forward declaration (PIMPL)

/**
 * Helps one to log messages.
 * It is a singleton.
 */
class Logger
{
    public:
        // typedef std::ostringstream Output;
        /**
         * Retrieves the singleton.
         */
        static Logger& getInstance();
        /**
         * Sets log level.
         */
        void setLevel(LogLevel level);
        LogLevel getLevel();
        /**
         * Logs a message.
         */
        static void log(LogLevel level, const char *message);
        static void log(LogLevel level, const std::ostringstream &os);
        static void log(LogLevel level, const std::string &text);
        /**
         * Returns true if messages of the specified LogLevel should be logged.
         */
        static bool isEnabledFor(LogLevel level);
        ~Logger();
    private:
        std::tr1::shared_ptr<LoggerPrivate> logger_private_;
        // Private constructor
        Logger();
        // Dont forget to declare these two. You want to make sure they
        // are unaccessable otherwise you may accidently get copies of
        // your singelton appearing.
        Logger(Logger const&);         // Don't Implement
        void operator=(Logger const&); // Don't implement
        LogLevel level_;
};

// TODO: provide signals

} // end of namespace

#endif // ifndef

