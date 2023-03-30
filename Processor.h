#pragma once
#include "Types.h"
#include "CommandManager.h"

class Processor {
private:
	List<ExternalNode> CSS;
	CommandManager manager;

	bool modeCSS,attributes;
	int starCounter, questionCounter, numberOfSections;
	myString currentInputString;

	Section* section;
	Node<myString>* selector;
	Node<AttributeNode>* attributeNode;
public:
	Processor();
	~Processor();
	void manageInput(const char inputChar);
private:
	bool modeManager(const char inputChar);

	void inputCSS(const char inputChar);
	void inputCommand(const char inputChar);
	
	void saveSelector();
	void saveAttribute();
	
	SectionAndBlockNumber getXsection(int x);
	void addSection(int index, int whichExternalNode);
	void addNewNodeAndSection();
	void endSection();
	bool deleteSection(int x);

	void commandDispatcher();
	
	void iSj_Command();
	void iAn_Command();
	void zEn_Command();
	void iDn_Command();
	void iSquestion_Command();
	void iAquestion_Command();
	void nAquestion_Command();
	void zSquestion_Command();
};

