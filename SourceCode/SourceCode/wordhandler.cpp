module wordhandler;
using skribbl::WordHandler;

void WordHandler::readFromFile()
{
	std::ifstream m_fin(m_fileName);
	if (!m_fin.is_open()) {
		throw std::exception("File was unable to be oppened");
	}
	std::string word;
	while (m_fin >> word)
		m_words.push_back(word);
	m_fin.close();
}

int WordHandler::randomIndex(int size) const
{
	return (rand() % (size));
}

WordHandler::WordHandler(const std::string& fileName) : m_fileName{ fileName }
{

	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	srand(seed); 
	readFromFile();
	update();
}


void WordHandler::update()
{
	if (m_words.size() == 0)
		std::exception("There are no words left");
	std::erase(m_words, m_currentWord);
	m_currentWord = m_words[randomIndex(m_words.size())];
}

std::string WordHandler::getWord() const
{
	return m_currentWord;
}


/*
std::vector<std::pair<int, char>> skribbl::WordHandler::getHint() 
{
	if (m_currentWord.size() == 0) {
		return {};
	}
	
	UniqueRandom ur(m_currentWord.size());

	std::vector<std::pair<int, char>> m_hint;
	for (int i = 0; i < m_currentWord.size()/2; i++) {
		int index = ur.getValue();
		m_hint.push_back({index, m_currentWord[index]});
	}

	return m_hint;
}
*/