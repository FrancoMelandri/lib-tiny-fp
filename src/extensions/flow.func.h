namespace TinyFp::Extensions
{
    template <class S>
    S loop(function<S()> init, function<bool(const S&)> enabled, function<S(const S&)> body)
    {
        auto current = init();
        while(enabled(current))
        {
            auto nextstate = body(current);
            current = nextstate;
        }
        return current;
    }
}