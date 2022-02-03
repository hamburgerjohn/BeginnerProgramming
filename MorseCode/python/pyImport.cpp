#include "../includes/MorseCodeDecipher.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace Morse;

PYBIND11_MODULE(morse, handle){
    handle.doc() = "Module for import c++";

    py::class_<Morse::MorseCodeDecipher>(
        handle, "PyMorseCodeDecipher"
    )
    .def(py::init<const char*>())
    .def(py::init<>())
    .def("ConvertToEnglish", &MorseCodeDecipher::ConvertToEnglish)
    .def("SetFilename", &MorseCodeDecipher::SetFilename)
    .def("Decipher", &MorseCodeDecipher::Decipher)
    .def("GetDecipheredCode", &MorseCodeDecipher::GetDecipheredCode);

    py::class_<Morse::MorseCodePlayer>(
        handle, "PyMorseCodePlayer"
    )
    .def(py::init<const char*>())
    .def(py::init<>())
    .def("ConvertToMorse", &MorseCodePlayer::ConvertToMorse)
    .def("InitWAVE", &MorseCodePlayer::InitWAVE);

}

