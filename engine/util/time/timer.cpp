/***************************************************************************
*   Copyright (C) 2005-2007 by the FIFE Team                              *
*   fife-public@lists.sourceforge.net                                     *
*   This file is part of FIFE.                                            *
*                                                                         *
*   FIFE is free software; you can redistribute it and/or modify          *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA              *
***************************************************************************/
// Standard C++ library includes

// 3rd party library includes

// FIFE includes
// These includes are split up in two parts, separated by one empty line
// First block: files included from the FIFE root src directory
// Second block: files included from the same folder
#include "timemanager.h"
#include "timer.h"

namespace FIFE {

	// Remember TimeEvent(-1) means that even an registered event won't be called
	Timer::Timer() 
		: TimeEvent(-1), 
		m_active(false) {
	}

	Timer::~Timer() {
		stop();
	}

	void Timer::start() {
		if(m_active)
			return;
		setLastUpdateTime( TimeManager::instance()->getTime() );
		TimeManager::instance()->registerEvent(this);
		m_active = true;
	}

	void Timer::stop() {
		if(!m_active)
			return;
		TimeManager::instance()->unregisterEvent(this);
		m_active = false;
	}

	void Timer::setInterval(unsigned long msec) {
		setPeriod(msec);
		stop();
	}
	void Timer::setCallback(const type_callback& cb) {
		m_callback = cb;
	}

	void Timer::setListener(TimerListener* listener) {
		m_listener = listener;
	}

	void Timer::updateEvent(unsigned long) {
		if(!m_active)
			return;

		if( m_callback ) {
			m_callback();
		}
		if ( m_listener ) {
			m_listener->onTimer();
		}
	}
}
