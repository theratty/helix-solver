#include <fstream>
#include <HelixSolver/TrackFindingAlgorithm.h>
#include <boost/math/constants/constants.hpp>

namespace HelixSolver {

    TrackFindingAlgorithm::TrackFindingAlgorithm(nlohmann::json &p_config, const std::vector<Stub> &p_stubs)
            : m_config(p_config), m_B(p_config["B"].get<double>()), m_stubs(p_stubs),
              m_firstStageAcc(m_config["main_accumulator_config"], m_stubs) {
    }

    void TrackFindingAlgorithm::Run() {
        m_firstStageAcc.Fill();
        VectorIdxPair cellsAboveThreshold = m_firstStageAcc.GetCellsAboveThreshold(
                m_config["threshold"].get<uint8_t>());

        std::ofstream out(m_config["outputFile"].get<std::string_view>());
        out << std::setprecision(64);
        for (auto &p : cellsAboveThreshold) {
            const auto[q_over_p, angle] = m_firstStageAcc.GetValuesOfIndexes(p.first, p.second);
            double r = ((1 / q_over_p) / m_B) * 1000;
            double phi = angle + boost::math::constants::pi<double>() / 2;
            out << r << " " << phi << std::endl;
        }
    }

} // namespace HelixSolver