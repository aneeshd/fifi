// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <sak/easy_bind.hpp>

namespace fifi
{
    /// The super_region_dispatcher layer will bind the region
    /// arithmetic functions to Super's region arithmetic
    /// functions. Typically this layer will be the last after a
    /// number of stack_region_dispatchers.
    ///
    /// When used in this way the super_region_dispatcher serves as
    /// the fallthrough / catch-all layer it will make sure that if
    /// non of the optimized stacks in the stack_region_dispatcher
    /// layers implements the call it will simply be forwarded to the
    /// Super's region arithithmetics (which typically represent the
    /// basic implementations e.g. non SIMD optimzed function).
    template<class Super>
    class super_region_dispatcher : public Super
    {
    public:

        /// @copydoc layer::value_type
        using value_type = typename Super::value_type;

        /// @copydoc layer::region_add(value_type*, const value_type*,
        ///                            uint32_t) const
        using call_region_add = std::function<
            void (value_type*, const value_type*, uint32_t)>;

        /// @copydoc layer::region_subtract(value_type*, const value_type*,
        ///                                 uint32_t) const
        using call_region_subtract = std::function<
            void (value_type*, const value_type*, uint32_t)>;


        /// @copydoc layer::region_divide(value_type*, const value_type*,
        ///                               uint32_t) const
        using call_region_divide = std::function<
            void (value_type*, const value_type*, uint32_t)>;

        /// @copydoc layer::region_multiply(value_type*, const value_type*,
        ///                                 uint32_t) const
        using call_region_multiply = std::function<
            void (value_type*, const value_type*, uint32_t)>;

        /// @copydoc layer::region_multiply_constant(value_type*, value_type,
        ///                                          uint32_t) const
        using call_region_multiply_constant = std::function<
            void (value_type*, value_type, uint32_t)>;

        /// @copydoc layer::region_multiply_add(value_type*, const value_type*,
        ///                                     value_type, uint32_t) const
        using call_region_multiply_add = std::function<
            void (value_type*, const value_type*, value_type, uint32_t)>;

        /// @copydoc layer::region_multiply_subtract(value_type*,
        ///                                          const value_type*,
        ///                                          value_type,
        ///                                          uint32_t) const
        using call_region_multiply_subtract = std::function<
            void (value_type*, const value_type*, value_type, uint32_t)>;

    public:

        /// @copydoc layer::dispatch_region_add() const
        auto dispatch_region_add() const ->
            call_region_add
        {
            return sak::easy_bind(&Super::region_add, this);
        }

        /// @copydoc layer::dispatch_region_subtract() const
        auto dispatch_region_subtract() const ->
            call_region_subtract
        {
            return sak::easy_bind(&Super::region_subtract, this);
        }

        /// @copydoc layer::dispatch_region_divide() const
        auto dispatch_region_divide() const ->
            call_region_divide
        {
            return sak::easy_bind(&Super::region_divide, this);
        }

        /// @copydoc layer::dispatch_region_multiply() const
        auto dispatch_region_multiply() const ->
            call_region_multiply
        {
            return sak::easy_bind(&Super::region_multiply, this);
        }

        /// @copydoc layer::dispatch_region_multiply_constant() const
        auto dispatch_region_multiply_constant() const ->
            call_region_multiply_constant
        {
            return sak::easy_bind(&Super::region_multiply_constant, this);
        }

        /// @copydoc layer::dispatch_region_multiply_add() const
        auto dispatch_region_multiply_add() const ->
            call_region_multiply_add
        {
            return sak::easy_bind(&Super::region_multiply_add, this);
        }

        /// @copydoc layer::dispatch_region_multiply_subtract() const
        auto dispatch_region_multiply_subtract() const ->
            call_region_multiply_subtract
        {
            return sak::easy_bind(&Super::region_multiply_subtract, this);
        }
    };
}
