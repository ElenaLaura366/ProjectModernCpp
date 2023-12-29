module wordhandler;
using skribbl::WordHandler;

std::string WordHandler::GetWord()
{
	return m_currentWord;
}



std::string WordHandler::GetHint() const
{
	if (m_currentWord.size() == 0) {
		return {};
	}
	UniqueRandom<int> randomPossitions(m_currentWord.size());

	std::string m_hint;
	for (char chr : m_currentWord)
		m_hint += "_";

	for (int index = 0; index < m_currentWord.size()/2; index++) {
		int pos = randomPossitions.GetValue();
		m_hint[pos] = m_currentWord[pos];
	}

	return m_hint;
}

void skribbl::WordHandler::Reset()
{

}
