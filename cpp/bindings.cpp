#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include "lda.h"
#include "lda_inference.h"
namespace py = pybind11;
using namespace std;

PYBIND11_MODULE(fastlda, m) {
    py::class_<LDA>(m, "LDA")
        .def(py::init<const vector<vector<size_t>> &, const size_t &,
                      const size_t &, const float &, const float & >(),
                      R"pbdoc(
                          Latent Dirichlet Allocation
                      )pbdoc")
        .def("estimate", &LDA::estimate, "Estimate LDA parameters",
             py::arg("num_iterations") = 100, py::arg("calc_perp") = false)
        .def("calculate_perplexity", &LDA::calculate_perplexity)
        .def("getTopicTermMatrix", &LDA::getTopicTermMatrix)
        .def("getDocTopicMatrix", &LDA::getDocTopicMatrix);

    m.doc() = R"pbdoc(
        Latent Dirichlet Allocation training module exposed to Python
        -----------------------
           estimate
           getTopicTermMatrix
           getDocTopicMatrix
    )pbdoc";

    py::class_<LDA_Inference>(m, "LDA_Inference")
        .def(py::init<const vector<vector<float>> &, const float & >(),
            "Inference module for Latent Dirichlet Allocation")
        .def("infer", &LDA_Inference::infer,
            "Infer latent topics for a document");

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
