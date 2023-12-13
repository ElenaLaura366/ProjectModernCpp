module wordhandler;
using skribbl::WordHandler;

std::string WordHandler::GetWord() const
{
	return m_currentWord;
}



std::vector<std::pair<int, char>> skribbl::WordHandler::GetHint() 
{
	if (m_currentWord.size() == 0) {
		return {};
	}

	m_ur = std::make_unique<UniqueRandom>(m_currentWord.size());
	std::vector<std::pair<int, char>> m_hint;
	for (int i = 0; i < m_currentWord.size()/2; i++) {
		int index = m_ur->getValue();
		m_hint.push_back({index, m_currentWord[index]});
	}

	return m_hint;
}
