#include <uhd/types/tune_request.hpp>
#include <uhd/usrp/multi_usrp.hpp>

#include <boost/format.hpp>
#include <boost/python.hpp>

#include <iostream>

using namespace boost::python;

struct VNA
{
    uhd::usrp::multi_usrp::sptr usrp;

    VNA(std::string uhdargs) {
        this->usrp = uhd::usrp::multi_usrp::make(uhdargs);

        std::cout << "Setting clock source to internal..." << std::endl;
        this->usrp->set_clock_source("internal");

        std::cout << "Setting sample rates..." << std::endl;
        this->usrp->set_rx_rate(1e6);
        this->usrp->set_tx_rate(1e6);

        std::cout << "Setting RF gains..." << std::endl;
        this->usrp->set_rx_gain(10);
        this->usrp->set_tx_gain(10);

        std::cout << "Ready." << std::endl;
    }

    std::string hello() {
        return "Hello!";
    }

    std::complex<double> point(double freq, double power) {
        double ifbw = 100e3;

        std::cout << boost::format("Tuning source to %f MHz...") % (freq / 1e6) << std::endl;
        uhd::tune_request_t tx_tune_request(freq);
        this->usrp->set_tx_freq(tx_tune_request);

        std::cout << boost::format("Tuning receiver offset by %f Hz...") % ifbw << std::endl;
        uhd::tune_request_t rx_tune_request(freq - ifbw);
        this->usrp->set_rx_freq(rx_tune_request);

        std::cout << boost::format("Setting source power to %f dBm...") % power << std::endl;

        std::cout << "Done." << std::endl;

        // XXX
        return std::complex<double>(0, 0);
    }
};

BOOST_PYTHON_MODULE(_native)
{
    class_<VNA>("VNA", init<std::string>())
        .def("hello", &VNA::point)
        .def("point", &VNA::point)
    ;
}
