namespace parser {
    template <char C0, char... Cs>
    struct is_number  // ..
        : std::conditional_t<(is_number<C0>::value) || C0 == '.'
            , is_number<Cs...>, std::false_type>
    {};

    template <char C>
    struct is_number<C>
        : std::conditional_t<(C >= '0' && C <= '9'), std::true_type, std::false_type>
    {};
}
