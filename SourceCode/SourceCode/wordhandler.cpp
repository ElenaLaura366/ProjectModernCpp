module wordhandler;
using skribbl::WordHandler;

void WordHandler::ReadFromFile()
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

int WordHandler::RandomIndex(int size) const
{
	return (rand() % (size));
}

WordHandler::WordHandler(const std::string& fileName) : m_fileName{ fileName }
{

	ur = new UniqueRandom(100);
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	srand(seed); 
	ReadFromFile();
	Update();
}


void WordHandler::Update()
{
	if (m_words.size() == 0)
		std::exception("There are no words left");
	std::erase(m_words, m_currentWord);
	m_currentWord = m_words[RandomIndex(m_words.size())];
}

std::string WordHandler::GetWord() const
{
	return m_currentWord;
}



std::vector<std::pair<int, char>> skribbl::WordHandler::GetHint() 
{
	if (m_currentWord.size() == 0) {
		return {};
	}
	

	ur = new UniqueRandom(m_currentWord.size());
	std::vector<std::pair<int, char>> m_hint;
	for (int i = 0; i < m_currentWord.size()/2; i++) {
		int index = ur->GetValue();
		m_hint.push_back({index, m_currentWord[index]});
	}

	return m_hint;
}
