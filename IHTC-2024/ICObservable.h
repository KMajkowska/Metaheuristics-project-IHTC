#pragma once

/**
 * @brief Observator design pattern
 * @tparam T any data type to be observed
 */
template <typename T>
class ICObservable
{
public:
	using Observer = std::function<void(T)>; /// Observer function type

	ICObservable() = default;

	/**
	 * @brief Moving to observer list
	 * @param observer Observer to be moves to observer list
	 */
	void addObserver(Observer observer);

	/**
	 * @brief notify all _observers about the change
	 * @param value value to inform _observers about
	 */
	void notify(T value);

private:
	std::vector<Observer> _observers;

};

template<typename T>
inline void ICObservable<T>::addObserver(Observer observer)
{
	_observers.push_back(std::move(observer));
}

template<typename T>
inline void ICObservable<T>::notify(T value)
{
	for (auto& obs : _observers)
	{
		obs(value);
	}
}
