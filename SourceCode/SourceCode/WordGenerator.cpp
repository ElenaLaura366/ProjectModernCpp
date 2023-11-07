import wordgenerator;
using skribbl::WordGenerator;

void WordGenerator::readFromFile()
{
	std::ifstream m_fin(m_fileName);
	if (!m_fin.is_open()) {
		std::exception("File with unable to be oppened");
	}
	std::string word;
	while (m_fin >> word)
		m_words.push_back(word);
	m_fin.close();
}

int WordGenerator::randomIndex(int size) const
{
	return (rand() % (size));
}

WordGenerator::WordGenerator(const std::string& fileName) : m_fileName(fileName)
{
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	srand(seed); // de facut pentru time(0)
	readFromFile();
	update();
}

void WordGenerator::update()
{
	if (m_words.size() == 0)
		std::exception("There are no words left");
	std::erase(m_words, m_currentWord);
	m_currentWord = m_words[randomIndex(m_words.size())];
	m_availableChars = std::vector<char>(m_currentWord.begin(), m_currentWord.end());
}

std::string WordGenerator::getWord() const
{
	return m_currentWord;
}

uint8_t WordGenerator::getLetter()
{
	if (!availableLetters())
		std::exception("No available letters");
	uint8_t index = randomIndex(m_availableChars.size());
	char currrent = m_availableChars[index];
	m_availableChars.erase(m_availableChars.begin() + index); // nu e asa okay ca am o prelucrare de date in interiorul unui getter

	return index;
}

bool WordGenerator::availableLetters()
{
	return (m_availableChars.size() > 0);
}

std::string skribbl::WordGenerator::getWordPattern() const 
{	
	if (m_currentWord.size() == 0) {
		return "";
	}
	std::string pattern(2*m_currentWord.size(), '_');
	for(int i = 1; i < pattern.size(); i+=2)
		pattern[i] = ' ';
	return pattern;
}

std::string skribbl::WordGenerator::getHint() 
{
	if (m_currentWord.size() == 0) {
		return "";
	}
	
	std::string pattern = getWordPattern();
	for (int i = 0; i < m_currentWord.size()/2; i++) {
		uint8_t index = getLetter();
		pattern[2 * index] = m_currentWord[index];
	}

	return  std::format("English Word with {} letters: {}", m_currentWord.size(), pattern);
}
