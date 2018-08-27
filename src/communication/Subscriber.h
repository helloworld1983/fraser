/*
 * Copyright (c) 2017, German Aerospace Center (DLR)
 *
 * This file is part of the development version of FRASER.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Authors:
 * - 2017, Annika Ofenloch (DLR RY-AVS)
 */

#ifndef SUBSCRIBER_H_
#define SUBSCRIBER_H_

#include <iostream>
#include <zmq.hpp>

#include "zhelpers.hpp"

class Subscriber {
public:
	Subscriber(zmq::context_t & ctx);
	virtual ~Subscriber();

	// forbid copying
	Subscriber(Subscriber const &) = delete;
	Subscriber & operator=(Subscriber const &) = delete;

	//protected:
	bool connectToPub(std::string ip, std::string port);
	bool prepareSubSynchronization(std::string ip, std::string port);
	bool synchronizeSub();

	void subscribeTo(std::string eventName);

	bool receiveEvent(bool noBlock = false);

	std::string getEventName() {
		return mEventName;
	}

	void* getEventBuffer() {
		return mEventBuffer;
	}

	void setOwnershipName(std::string name) {
		mOwner = name;
	}

private:
	zmq::context_t &mZMQcontext;
	zmq::socket_t mZMQsubscriber;
	zmq::socket_t mZMQSyncService;

	std::string mOwner;
	std::string mEventName;
	void* mEventBuffer;
};

#endif /* SUBSCRIBER_H_ */
