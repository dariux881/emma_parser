/*
 * Interpretation.h
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#ifndef INTERPRETATION_H_
#define INTERPRETATION_H_

#include "config.h"
#include "Container/Container.h"
#include "Grammar.h"
#include "Model.h"
#include "DerivedFrom.h"
#include <vector>
#include <string>

using namespace std;

class Container;

class Interpretation {
public:
	EMMAPARSER_API Interpretation();
	EMMAPARSER_API virtual ~Interpretation();

	EMMAPARSER_API void setId(string id) { this->id = id; }
	EMMAPARSER_API void setContainerParent(Container* par) { this->parent = par; }
	EMMAPARSER_API void setConfidence(float confidence) { this->confidence = confidence; }
	EMMAPARSER_API void setMedium(const string& medium) { this->medium = medium; }
	EMMAPARSER_API void setMode(const string& mode) { this->mode = mode; }
	EMMAPARSER_API void setNoInput(bool noInput) { this->no_input = noInput; }
	EMMAPARSER_API void setStart(unsigned long long start);
	EMMAPARSER_API void setDuration(unsigned long long duration);
	EMMAPARSER_API void setEnd(unsigned long long end);
	EMMAPARSER_API void setTokens(const string& tokens) { this->tokens = tokens; }
	EMMAPARSER_API void setUninterpreted(bool uninterpreted) { this->uninterpreted = uninterpreted; }
	EMMAPARSER_API void setCost(float cost) { this->cost = cost; }
	EMMAPARSER_API void setDialogTurn(string dialogTurn) { this->dialog_turn = dialogTurn; }
	EMMAPARSER_API void setFunction(string function) { this->function = function; }
	EMMAPARSER_API void setGrammarRef(string grammarRef) { this->grammar_ref = grammarRef; }
	EMMAPARSER_API void setLang(string lang) { this->lang = lang; }
	EMMAPARSER_API void setMediaType(string mediaType) { this->media_type = mediaType; }
	EMMAPARSER_API void setModelRef(string modelRef) { this->model_ref = modelRef; }
	EMMAPARSER_API void setOffsetToStart(long offsetToStart) { this->offset_to_start = offsetToStart; }
	EMMAPARSER_API void setProcess(string process) { this->process = process; }
	EMMAPARSER_API void setSignal(string signal) { this->signal = signal; }
	EMMAPARSER_API void setSignalSize(unsigned long long signalSize) { this->signal_size = signalSize; }
	EMMAPARSER_API void setSource(string source) { this->source = source; }
	EMMAPARSER_API void setTimeRefAnchorPoint(string timeRefAnchorPoint) { this->time_ref_anchor_point = timeRefAnchorPoint; }
	EMMAPARSER_API void setTimeRefUri(string timeRefUri) { this->time_ref_uri = timeRefUri; }
	EMMAPARSER_API void setVerbal(bool verbal) { this->verbal = verbal; }
	EMMAPARSER_API void setGrammarRef(Grammar* ref) { this->grammarRef = ref; }
	EMMAPARSER_API void setModelRef(Model* ref) { this->modelRef = ref; }
	EMMAPARSER_API void addDerivedFrom(DerivedFrom* derivedFrom);

	EMMAPARSER_API string			getId() { return this->id; }
	EMMAPARSER_API float 			getConfidence() { return this->confidence; }
	EMMAPARSER_API unsigned long long 	getDuration() { return (this->end- this->start); }
	EMMAPARSER_API unsigned long long 	getEnd() { return this->end; }
	EMMAPARSER_API const string& 	getMedium() { return this->medium; }
	EMMAPARSER_API const string& 	getMode() { return this->mode; }
	EMMAPARSER_API bool 			isNoInput() { return this->no_input; }
	EMMAPARSER_API Container* 		getParent() { return this->parent; }
	EMMAPARSER_API unsigned long long 	getStart() { return this->start; }
	EMMAPARSER_API const string& 	getTokens() { return this->tokens; }
	EMMAPARSER_API bool 			isUninterpreted() { return this->uninterpreted; }
	EMMAPARSER_API float 			getCost() { return this->cost; }
	EMMAPARSER_API string 			getDialogTurn() { return this->dialog_turn; }
	EMMAPARSER_API string 			getFunction() { return this->function; }
	EMMAPARSER_API string 			getLang() { return this->lang; }
	EMMAPARSER_API string 			getMediaType() { return this->media_type; }
	EMMAPARSER_API string 			getModelRefId() { return this->model_ref; }
	EMMAPARSER_API string	 		getGrammarRefId() { return this->grammar_ref; }
	EMMAPARSER_API Model* 			getModelRef() { return this->modelRef; }
	EMMAPARSER_API Grammar* 		getGrammarRef() { return this->grammarRef; }
	EMMAPARSER_API long 			getOffsetToStart() { return this->offset_to_start; }
	EMMAPARSER_API string 			getProcess() { return this->process; }
	EMMAPARSER_API string 			getSignal() { return this->signal; }
	EMMAPARSER_API unsigned long long 	getSignalSize() { return this->signal_size; }
	EMMAPARSER_API string 			getSource() { return this->source; }
	EMMAPARSER_API string 			getTimeRefAnchorPoint() { return this->time_ref_anchor_point; }
	EMMAPARSER_API string 			getTimeRefUri() { return this->time_ref_uri; }
	EMMAPARSER_API bool 			isVerbal() { return this->verbal; }
	EMMAPARSER_API vector<DerivedFrom*> getDerivedFrom() { return this->derivedFrom; }

	EMMAPARSER_API string 			toString();

private:
	string			attributesToString();

	string			id;
	unsigned long long 	start, end, signal_size;
	long			offset_to_start;
	float 			confidence, cost;
	string			tokens, medium, mode;
	string			process, lang, signal, source, function, dialog_turn, media_type;
	string			model_ref, grammar_ref, time_ref_uri, time_ref_anchor_point;
	Grammar*		grammarRef;
	Model*			modelRef;
	bool			no_input, uninterpreted, verbal;

	Container*		parent;
	vector<DerivedFrom*>	derivedFrom;
};

#endif /* INTERPRETATION_H_ */
