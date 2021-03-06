#ifndef HAL_LIBS_TERMINAL_TERMINAL_H_
#define HAL_LIBS_TERMINAL_TERMINAL_H_

#include <cstdint>
#include <gsl/gsl>

/**
 * @defgroup terminal Terminal module
 *
 * @{
 */

/**
 * @brief Type of function used as terminal command handler
 */
using TerminalCommandHandler = void (*)(gsl::span<char*>);

/**
 * Structure describing single terminal command
 */
struct TerminalCommandDescription {
    /** @brief Name of the command */
    const char* name;
    /** Pointer to handler function */
    TerminalCommandHandler handler;
};

/**
 * @brief Terminal class
 */
class Terminal {
public:
    /**
     * @brief Sets supported commands list
     * @param[in] commands Commands list
     */
    void SetCommandList(gsl::span<const TerminalCommandDescription> commands);

    /**
     * @brief Starts terminal
     */
    void Initialize();

    /**
     * @brief Handles incoming command
     * @param[in] buffer Buffer with incoming command
     *
     * After this method ends, @p buffer is no longer usable
     */
    void HandleCommand(char* buffer);

private:
    /**
     * @brief Command list
     */
    gsl::span<const TerminalCommandDescription> _commandList;
};

/** @} */

#endif  // HAL_LIBS_TERMINAL_TERMINAL_H_