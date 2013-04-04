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

#include "entity/logger.h"
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <iostream>

namespace entity {

struct LoggerPrivate
{
    public:
        log4cpp::Appender *appender_;
        log4cpp::PatternLayout *layout_;
        static const char * const category_name_;
        LoggerPrivate(LogLevel initial_level);
        ~LoggerPrivate();
};

Logger& Logger::getInstance()
{
    static Logger instance; // Guaranteed to be destroyed.
    return instance; // Instantiated on first use.
}

void Logger::setLevel(LogLevel level)
{
    level_ = level;
    log4cpp::Category& category = log4cpp::Category::getInstance(this->logger_private_->category_name_);
    category.setPriority(level_);
}

bool Logger::isEnabledFor(LogLevel level)
{
    return level <= Logger::getInstance().getLevel();
}

LogLevel Logger::getLevel()
{
    return level_;
}

void Logger::log(LogLevel level, const std::ostringstream &os)
{
    Logger::log(level, os.str().c_str());
}

void Logger::log(LogLevel level, const std::string &text)
{
    Logger::log(level, text.c_str());
}

void Logger::log(LogLevel level, const char *message)
{
    Logger &self = Logger::getInstance();
    log4cpp::Category& category = log4cpp::Category::getInstance(self.logger_private_->category_name_);
    switch (level)
    {
        case DEBUG:
            category.debug(message);
            break;
        case INFO:
            category.info(message);
            break;
        case NOTICE:
            category.notice(message);
            break;
        case WARNING:
            category.warn(message);
            break;
        case CRITICAL:
            category.crit(message);
            break;
        case ERROR:
            category.error(message);
            break;
    }
}

Logger::~Logger()
{
}

LoggerPrivate::~LoggerPrivate()
{
    // No need to delete appender_ and layout_
}

Logger::Logger()
{
    this->level_ = WARNING; // default
    this->logger_private_.reset(new LoggerPrivate(this->level_));
}

LoggerPrivate::LoggerPrivate(LogLevel initial_level)
{
    this->appender_ = new log4cpp::OstreamAppender("console", &std::cout);
    this->layout_ = new log4cpp::PatternLayout();
    this->layout_->setConversionPattern("%d{%H:%M:%S,%l} %8p - %m %n"); // %d: 
    this->appender_->setLayout(layout_);
    log4cpp::Category& category = log4cpp::Category::getInstance(this->category_name_);
    category.setAppender(this->appender_);
    category.setPriority(initial_level); //default
}

const char * const LoggerPrivate::category_name_ = "default";

} // end of namespace

