/**

    @file      expected_assert.inl
    @author    Khrapov
    @date      31.10.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

inline expected_assert_builder::string_matcher::string_matcher(string_view svValue, bool bRegex) : m_Value(svValue)
{
    if (bRegex)
        m_Regex.emplace(svValue.begin(), svValue.end());
}

inline bool expected_assert_builder::string_matcher::matches(string_view svValue) const
{
    return m_Regex ? std::regex_search(svValue.begin(), svValue.end(), *m_Regex) : svValue == m_Value;
}

inline string_view expected_assert_builder::string_matcher::get_pattern() const
{
    return m_Value;
}

inline bool expected_assert_builder::string_matcher::is_regex() const
{
    return m_Regex.has_value();
}

inline expected_assert_builder& expected_assert_builder::condition(string_view svCondition, bool bRegex)
{
    m_Condition.emplace(svCondition, bRegex);
    return *this;
}

inline expected_assert_builder& expected_assert_builder::category(const qx::category& category)
{
    m_pCategory = &category;
    return *this;
}

inline expected_assert_builder& expected_assert_builder::type(assert_type eType)
{
    m_Type = eType;
    return *this;
}

inline expected_assert_builder& expected_assert_builder::message(string_view svPattern, bool bRegex)
{
    m_Message.emplace(svPattern, bRegex);
    return *this;
}

inline expected_assert_builder& expected_assert_builder::function(string_view svFunction, bool bRegex)
{
    m_Function.emplace(svFunction, bRegex);
    return *this;
}

inline expected_assert_builder& expected_assert_builder::file(string_view svFile, bool bRegex)
{
    m_File.emplace(svFile, bRegex);
    return *this;
}

inline expected_assert_builder& expected_assert_builder::line(i32 nLine)
{
    m_Line = nLine;
    return *this;
}

inline expected_assert_builder& expected_assert_builder::count(size_t nCount)
{
    m_nCount = nCount;
    return *this;
}

inline expected_assert expected_assert_builder::build() const
{
    return expected_assert(*this);
}

inline expected_assert::expected_assert(const expected_assert_builder& builder) : m_Builder(builder)
{
    asserts_manager::get_instance().add_interceptor(
        this,
        [this](
            string_view         svCondition,
            const qx::category& category,
            assert_type         eType,
            string_view         svMessage,
            string_view         svFunction,
            string_view         svFile,
            i32                 nLine)
        {
            if (m_Builder.m_Condition && !m_Builder.m_Condition->matches(svCondition))
                return false;

            if (m_Builder.m_pCategory && *m_Builder.m_pCategory != category)
                return false;

            if (m_Builder.m_Type && eType != *m_Builder.m_Type)
                return false;

            if (m_Builder.m_Message && !m_Builder.m_Message->matches(svMessage))
                return false;

            if (m_Builder.m_Function && !m_Builder.m_Function->matches(svFunction))
                return false;

            if (m_Builder.m_File && !m_Builder.m_File->matches(svFile))
                return false;

            if (m_Builder.m_Line && nLine != *m_Builder.m_Line)
                return false;

            ++m_nActual;
            return true;
        });
}

inline expected_assert::~expected_assert()
{
    asserts_manager::get_instance().remove_interceptor(this);
    const size_t nActual = m_nActual.load();
    if (nActual != m_Builder.m_nCount)
    {
        string     sDetails;
        const auto AppendMatcher = [&sDetails](string_view svName, const auto& optMatcher)
        {
            if (optMatcher)
            {
                sDetails.append_format(
                    QXT("\n  {}{}: {}"),
                    svName,
                    optMatcher->is_regex() ? QXT(" (regex)") : QXT(""),
                    optMatcher->get_pattern());
            }
        };

        AppendMatcher(QXT("condition"), m_Builder.m_Condition);

        if (m_Builder.m_pCategory)
            sDetails.append_format(QXT("\n  category: {}"), m_Builder.m_pCategory->get_name());

        if (m_Builder.m_Type)
            sDetails.append_format(QXT("\n  type: {}"), *m_Builder.m_Type);

        AppendMatcher(QXT("message"), m_Builder.m_Message);

        AppendMatcher(QXT("function"), m_Builder.m_Function);

        AppendMatcher(QXT("file"), m_Builder.m_File);

        if (m_Builder.m_Line)
            sDetails.append_format(QXT("\n  line: {}"), *m_Builder.m_Line);

        ADD_FAILURE() << "Expected " << m_Builder.m_nCount << " matching assertions, got " << nActual
                      << to_cstring(sDetails).c_str();
    }
}

} // namespace qx
