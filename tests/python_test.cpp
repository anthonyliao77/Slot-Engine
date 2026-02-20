#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h> // Specialized STL headers in nanobind
#include <nanobind/stl/map.h>
#include "reel_strip.h"

namespace nb = nanobind;

NB_MODULE(slot_engine, m) {
    nb::class_<ReelStrip>(m, "ReelStrip")
        .def(nb::init<>())
        .def("size", &ReelStrip::size)
        .def("setSymbols", &ReelStrip::setSymbols);

    nb::class_<Reel>(m, "Reel")
        .def(nb::init<const ReelStrip&, std::size_t>(), nb::arg("strip"), nb::arg("start") = 0)
        .def("spin", &Reel::spin)
        .def("visibleSymbols", &Reel::visibleSymbols);
}