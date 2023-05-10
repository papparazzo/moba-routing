/*
 *  Project:    moba-blocksystem
 *
 *  Copyright (C) 2019 Stefan Paproth <pappi-@gmx.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/agpl.txt>.
 *
 */

#include <thread>
#include <moba-common/log.h>

#include "msgloop.h"
#include "moba/registry.h"
#include "moba/controlmessages.h"
#include "layoutparser.h"

MessageLoop::MessageLoop(EndpointPtr endpoint): endpoint{endpoint}, closing{false} {
}

void MessageLoop::run() {
    while(!closing) {
        try {
            Registry registry;
          //  registry.registerHandler<LayoutGetLayoutsRes_Derived>([this](const LayoutGetLayoutsRes_Derived &d) {parseLayout(d);});
          //  registry.registerHandler<InterfaceContactTriggered>([this](const InterfaceContactTriggered &d) {contactTriggered(d);});
          //  registry.registerHandler<ControlGetBlockListRes>([this](const ControlGetBlockListRes &d) {getFeedbackContactList(d);});
          //  registry.registerHandler<ControlGetSwitchStandListRes>([this](const ControlGetSwitchStandListRes &d) {getSwitchStates(d);});
          //  registry.registerHandler<ControlGetTrainListRes>([this](const ControlGetTrainListRes &d) {getTrainList(d);});

            //registry.registerHandler<ControlBlockLocked>([this](const ControlBlockLocked &d) {});
            //registry.registerHandler<ControlBlockLockingFailed>([this](const ControlBlockLockingFailed &d) {});
            registry.registerHandler<LayoutDefaultLayoutChanged>([this](const LayoutDefaultLayoutChanged &d) {endpoint->sendMsg(ControlGetBlockListReq{});});

            endpoint->connect();
            endpoint->sendMsg(ControlGetBlockListReq{});

            while(true) {
                registry.handleMsg(endpoint->waitForNewMsg());
            }
        } catch(const std::exception &e) {
          //  screen.printException(e.what());
        }
        std::this_thread::sleep_for(std::chrono::milliseconds{500});
    }
}
/*
void MessageLoop::getFeedbackContactList(const ControlGetBlockListRes &d) {
    blockContacts = d.blockContacts;
    endpoint->sendMsg(ControlGetSwitchStateListReq{});
}

void MessageLoop::getSwitchStates(const ControlGetSwitchStandListRes &d) {
    switchstates = d.switchstates;
    endpoint->sendMsg(ControlGetTrainListReq{});
}

void MessageLoop::getTrainList(const ControlGetTrainListRes &d) {
    trainList = d.trainList;
    endpoint->sendMsg(LayoutGetLayoutReadOnlyReq{});
}

void MessageLoop::parseLayout(const LayoutGetLayoutsRes_Derived &d) {
    LayoutParser parser;
    parser.parse(d.symbols, blockContacts, switchstates, trainList);

    blockMap = parser.getBlockMap();
    switchMap = parser.getSwitchMap();

    screen.setBlocks(blockMap);
    updateScreen();
}

void MessageLoop::contactTriggered(const InterfaceContactTriggered &d) {
    // Nur belegte Bloecke beruecksichtigen
    if(!d.contactTrigger.state) {
        return;
    }

    auto iter = blockMap->find(d.contactTrigger.contactData);

    // Wenn nicht in der Liste dann raus
    if(iter == blockMap->end()) {
        return;
    }

    auto block = iter->second->pushTrain();
    auto train = block->getTrain();

    endpoint->sendMsg(ControlPushTrain{train->id, iter->second->getId(), block->getId(), train->direction});

    // vorherigen Block freigeben:
    //endpoint->sendMsg(ControlUnlockBlock{1, 1});

    updateScreen();
}

void MessageLoop::updateScreen() {
    screen.draw();
}
*/