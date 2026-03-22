#include "VolatusConfig/VolatusConfig.hpp"

namespace Volatus {

    SystemConfig::SystemConfig(Config::Element* elem) : ConfigElement{elem} {
    }

    std::vector<ClusterConfig> SystemConfig::getClusters() {
        Config::Lookup clusterLookup;
        addTypeLookup(clusterLookup, ConfigType::VL_Cluster);

        auto elems = get()->lookupDescendents(clusterLookup);
        std::vector<ClusterConfig> clusters{};

        for (auto it = elems.begin(); it != elems.end(); ++it) {
            clusters.emplace_back(*it);
        }

        return clusters;
    }
}
