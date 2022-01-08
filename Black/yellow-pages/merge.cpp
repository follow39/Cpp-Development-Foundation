#include "yellow_pages.h"

#include <algorithm>
#include <tuple>

namespace YellowPages {

    Company Merge(const Signals &input_signals, const Providers &input_providers) {
        std::multimap<uint32_t, uint64_t> ids;
        for (const auto&[id, provider]: input_providers) {
            ids.emplace(provider.priority(), id);
        }

        std::unordered_map<uint64_t, Signals::const_iterator> signalsByProviderId;
        for (auto it = input_signals.begin(); it != input_signals.end(); ++it) {
            signalsByProviderId.emplace(it->provider_id(), it);
        }

        Company result;
        for (const auto&[priority, id]: ids) {
            auto &signal = *signalsByProviderId.at(id);
            auto &company = signal.company();

            if (company.has_address()) {
                result.clear_address();
                auto address = result.mutable_address();
                address->CopyFrom(company.address());
            }

            for (const auto &name: company.names()) {
                if (std::find_if(result.names().begin(), result.names().end(),
                                 [&name](const auto &arg) {
                                     return arg.SerializeAsString() == name.SerializeAsString();
                                 }) == result.names().end()) {
                    result.add_names()->CopyFrom(name);
                }
            }
            for (const auto &phone: company.phones()) {
                if (std::find_if(result.phones().begin(), result.phones().end(),
                                 [&phone](const auto &arg) {
                                     return arg.SerializeAsString() == phone.SerializeAsString();
                                 }) == result.phones().end()) {
                    result.add_phones()->CopyFrom(phone);
                }
            }
            for (const auto &url: company.urls()) {
                if (std::find_if(result.urls().begin(), result.urls().end(),
                                 [&url](const auto &arg) {
                                     return arg.SerializeAsString() == url.SerializeAsString();
                                 }) == result.urls().end()) {
                    result.add_urls()->CopyFrom(url);
                }
            }

            if (company.has_working_time()) {
                result.clear_working_time();
                auto working_time = result.mutable_working_time();
                working_time->CopyFrom(company.working_time());
            }
        }

        return std::move(result);
    }

}
