module;
export module wordgenerator;

export import <fstream>;
export import <vector>;
export import <string>;
import <chrono>;

namespace skribbl
{
	export class WordGenerator
	{
	private:
		void readFromFile();
		int randomIndex(int size) const;

	public:
		WordGenerator(const std::string& fileName);
		~WordGenerator() = default; 
		WordGenerator(const WordGenerator& wg)=delete; 
		WordGenerator& operator=(const WordGenerator&)=delete; 
		WordGenerator(const WordGenerator&& wg)=default;  
		WordGenerator& operator=(const WordGenerator&&) = default; 


		void update();
		std::string getWord() const;
		char getLetter(); // it will return one char
		bool availableLetters();

	private:
		std::vector<std::string> m_words;
		std::string m_currentWord;
		std::string m_fileName;
		std::vector<char> m_availableChars; // we'll see what container we'll use
	};
}