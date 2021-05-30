#pragma once

#include <chrono>
#include <vector>

namespace ast {
    // Measure time between time points.
    // _Type is number format to return (int, double, float)
    // _Ratio is std::ratio that shows time interval to return.
    // For example: std::ratio<1> is one second. Use some predefined values: std::nano, std::micro
    template <class _Type, class _Ratio = std::micro>
    class timer {
    private:
        typedef std::chrono::high_resolution_clock ast_clock;
        typedef std::chrono::duration<_Type, _Ratio> ast_duration;
        typedef std::chrono::time_point<ast_clock, ast_duration> ast_time_point;

        ast_time_point m_start;
        std::vector<_Type> m_history;
        bool m_isStarted;
    public:
        timer() noexcept : m_isStarted(false) {}

        void start() noexcept {
            if (!m_isStarted) {
                m_isStarted = true;
                m_start = std::chrono::time_point_cast<ast_duration>(ast_clock::now());
            }
        }

        const _Type stop() {
            if (m_isStarted) {
                ast_time_point stop = std::chrono::time_point_cast<ast_duration>(ast_clock::now());
                auto duration = std::chrono::duration_cast<ast_duration>(stop - m_start);
                m_isStarted = false;
                _Type ret = duration.count();
                m_history.push_back(ret);
                return ret;
            }
            return 0;
        }

        const _Type getLastDuration() const {
            return m_history.back();
        }

        const _Type operator[](std::size_t index) const {
            return m_history.at(index);
        }
    };
}