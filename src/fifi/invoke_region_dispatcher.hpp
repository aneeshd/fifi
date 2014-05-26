// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

namespace fifi
{
    /// The invoke_region_dispatcher implements the different region
    /// arithmetic functions. When called, it will dispatch the call to
    /// a stored function. To which specific function the call is
    /// dispached depends on the specific run-time platform, i.e. what
    /// type of hardware we are running on and what features are
    /// supported by the CPU.
    ///
    /// The invoke_region_dispatcher will obtain the function pointers
    /// from the lower layers by invoking the dispatch_xxx
    /// functions. These functions are typically implemented in the
    /// stack_region_dispatcher or super_region_dispatcher layers and
    /// will return function pointers if the hardware supports their
    /// specific optimizations.
    template<class Super>
    class invoke_region_dispatcher : public Super
    {
    public:

        /// @copydoc layer::value_type
        using value_type = typename Super::value_type;

        /// @copydoc layer::call_region_add
        using call_region_add =
            typename Super::call_region_add;

        /// @copydoc layer::call_region_subtract
        using call_region_subtract =
            typename Super::call_region_subtract;

        /// @copydoc layer::call_region_divide
        using call_region_divide =
            typename Super::call_region_divide;

        /// @copydoc layer::call_region_multiply
        using call_region_multiply =
            typename Super::call_region_multiply;

        /// @copydoc layer::call_region_multiply_constant
        using call_region_multiply_constant =
            typename Super::call_region_multiply_constant;

        /// @copydoc layer::call_region_multiply_add
        using call_region_multiply_add =
            typename Super::call_region_multiply_add;

        /// @copydoc layer::call_region_multiply_subtract
        using call_region_multiply_subtract =
            typename Super::call_region_multiply_subtract;

    public:

        /// Constructor initializes the stored member function pointers
        invoke_region_dispatcher()
        {
            m_region_add =
                Super::dispatch_region_add();

            m_region_subtract =
                Super::dispatch_region_subtract();

            m_region_divide =
                Super::dispatch_region_divide();

            m_region_multiply =
                Super::dispatch_region_multiply();

            m_region_multiply_constant =
                Super::dispatch_region_multiply_constant();

            m_region_multiply_add =
                Super::dispatch_region_multiply_add();

            m_region_multiply_subtract =
                Super::dispatch_region_multiply_subtract();

            // Ensure that all functions are initialized
            assert(m_region_add);
            assert(m_region_subtract);
            assert(m_region_divide);
            assert(m_region_multiply);
            assert(m_region_multiply_constant);
            assert(m_region_multiply_add);
            assert(m_region_multiply_subtract);
        }

        /// @copydoc layer::region_add(value_type*, const value_type*,
        ///                            uint32_t) const
        void region_add(value_type* dest, const value_type* src,
                        uint32_t length) const
        {
            m_region_add(dest, src, length);
        }

        /// @copydoc layer::region_subtract(value_type*, const value_type*,
        ///                                 uint32_t) const
        void region_subtract(value_type* dest, const value_type* src,
                             uint32_t length) const
        {
            m_region_subtract(dest, src, length);
        }

        /// @copydoc layer::region_divide(value_type*, const value_type*,
        ///                               uint32_t) const
        void region_divide(value_type* dest, const value_type* src,
                           uint32_t length) const
        {
            m_region_divide(dest, src, length);
        }

        /// @copydoc layer::region_multiply(value_type*, const value_type*,
        ///                                 uint32_t) const
        void region_multiply(value_type* dest, const value_type* src,
                             uint32_t length) const
        {
            m_region_multiply(dest, src, length);
        }

        /// @copydoc layer::region_multiply_constant(value_type*, value_type,
        ///                                          uint32_t) const
        void region_multiply_constant(value_type* dest, value_type constant,
                                      uint32_t length) const
        {
            m_region_multiply_constant(dest, constant, length);
        }

        /// @copydoc layer::region_multiply_add(value_type*, const value_type*,
        ///                                     value_type, uint32_t) const
        void region_multiply_add(value_type* dest,
                                 const value_type* src,
                                 value_type constant,
                                 uint32_t length) const
        {
            m_region_multiply_add(dest, src, constant, length);
        }

        /// @copydoc layer::region_multiply_subtract(value_type*,
        ///                                          const value_type*,
        ///                                          value_type,
        ///                                          uint32_t) const
        void region_multiply_subtract(value_type* dest,
                                      const value_type* src,
                                      value_type constant,
                                      uint32_t length) const
        {
            m_region_multiply_subtract(dest, src, constant, length);
        }

    protected:

        /// Function dispatch for region_add
        call_region_add m_region_add;

        /// Function dispatch for region_add
        call_region_subtract m_region_subtract;

        /// Function dispatch for region_add
        call_region_divide m_region_divide;

        /// Function dispatch for region_add
        call_region_multiply m_region_multiply;

        /// Function dispatch for region_add
        call_region_multiply_constant m_region_multiply_constant;

        /// Function dispatch for region_add
        call_region_multiply_add m_region_multiply_add;

        /// Function dispatch for region_add
        call_region_multiply_subtract m_region_multiply_subtract;
    };
}
