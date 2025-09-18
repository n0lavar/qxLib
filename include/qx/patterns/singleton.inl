/**

    @file      singleton.inl
    @author    Khrapov
    @date      19.09.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/

namespace qx
{

inline singletons_manager::~singletons_manager() noexcept
{
    while (!m_Singletons.empty())
        m_Singletons.pop_back();
}

inline singletons_manager& singletons_manager::get_instance() noexcept
{
    static singletons_manager instance;
    return instance;
}

inline void singletons_manager::add(std::unique_ptr<base_singleton> pSingleton) noexcept
{
    std::lock_guard _(m_SingletonsMutex);
    m_Singletons.push_back(std::move(pSingleton));
}

template<class T, class... dependencies_t>
    requires(std::is_base_of_v<base_singleton, dependencies_t> && ...)
T& singleton<T, dependencies_t...>::get_instance()
{
    static std::mutex instanceMutex;
    std::lock_guard   _(instanceMutex);

    static T* pSavedInstance = nullptr;
    if (!pSavedInstance) [[unlikely]]
    {
        (dependencies_t::get_instance(), ...);

        std::unique_ptr<T> pInstance = std::make_unique<T>();
        pInstance->init();
        pSavedInstance = pInstance.get();
        singletons_manager::get_instance().add(std::move(pInstance));
    }

    return *pSavedInstance;
}

template<class T, class... dependencies_t>
    requires(std::is_base_of_v<base_singleton, dependencies_t> && ...)
void singleton<T, dependencies_t...>::init()
{
}

} // namespace qx