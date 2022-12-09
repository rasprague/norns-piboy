//
// Created by emb on 11/18/18.
//

#include <iostream>
#include <chrono>
#include <thread>
#include <memory>

#include "MixerClient.h"
#include "SoftcutClient.h"
#include "OscInterface.h"
#include "BufDiskWorker.h"

static inline void sleep(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int main() {
    using namespace crone;
    using std::cout;
    using std::cerr;
    using std::endl;

#if 1
    std::unique_ptr<MixerClient> m = std::make_unique<MixerClient>();
    std::unique_ptr<SoftcutClient> sc = std::make_unique<SoftcutClient>();

    cout << "initializing buffer management worker.." << endl;
    BufDiskWorker::init(48000);

    cout << "setting up jack clients.." << endl;
    m->setup();
    sc->setup();

    cout << "starting jack clients.." << endl;
    m->start();
    sc->start();


    cout << "connecting ports... " << endl;
    try {
      m->connectAdcPorts();
    } catch (std::runtime_error const& ex) {
      cerr << ex.what() << endl;
      cerr << "Skipping." << endl;
    }
    m->connectDacPorts();
    m->connect<2, 2>(sc.get(), MixerClient::SinkCut, SoftcutClient::SourceAdc);
    sc->connect<6, 6>(m.get(), 0, MixerClient::SourceCut);

    cout << "starting OSC interface..." << endl;
    OscInterface::init(m.get(), sc.get());
    OscInterface::printServerMethods();

    cout << "entering main loop..." << endl;
    while(!OscInterface::shouldQuit())  {
        sleep(100);
    }

    cout << "stopping clients" << endl;
    m->stop();
    sc->stop();
    cout << "cleaning up clients..." << endl;
    m->cleanup();
    sc->cleanup();
    OscInterface::deinit();
    cout << "goodbye" << endl;
#else
    std::unique_ptr<SoftcutClient> sc;
    sc = std::make_unique<SoftcutClient>();

    sc->setup();
    sc->start();

    try {
      sc->connectAdcPorts();
    } catch (std::runtime_error const& ex) {
      cerr << ex.what() << endl;
      cerr << "Skipping." << endl;
    }
    sc->connectDacPorts();

    OscInterface::init();

    cout << "entering main loop..." << endl;
    while(!OscInterface::shouldQuit())  {
        sleep(100);
    }
    sc->stop();
    sc->cleanup();
#endif
    return 0;
}
