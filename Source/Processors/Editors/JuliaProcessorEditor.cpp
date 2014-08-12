/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2013 Open Ephys

    ------------------------------------------------------------------

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "JuliaProcessorEditor.h"
#include "../JuliaProcessor.h"

#include <stdio.h>

JuliaProcessorEditor::JuliaProcessorEditor(GenericProcessor* parentNode, bool useDefaultParameterEditors=true)
    : GenericEditor(parentNode, useDefaultParameterEditors)

{

    juliaProcessor = (JuliaProcessor*) parentNode;

    lastFilePath = File::getCurrentWorkingDirectory();

    fileButton = new UtilityButton("Select file",Font("Small Text", 13, Font::plain));
    fileButton->addListener(this);
    fileButton->setBounds(10,30,100,25);
    addAndMakeVisible(fileButton);

	reloadFileButton = new UtilityButton("refresh",Font("Small Text", 13, Font::plain));
    reloadFileButton->addListener(this);
    reloadFileButton->setBounds(100+10,30,60,25);
    addAndMakeVisible(reloadFileButton);


    fileNameLabel = new Label("FileNameLabel", "No file selected.");
    fileNameLabel->setBounds(10,50,140,25);
    addAndMakeVisible(fileNameLabel);

    desiredWidth = 200;

    setEnabledState(false);

}

JuliaProcessorEditor::~JuliaProcessorEditor()
{

}

void JuliaProcessorEditor::setFile(String file)
{

    File fileToRead(file);
    lastFilePath = fileToRead.getParentDirectory();
    juliaProcessor->setFile(fileToRead.getFullPathName());
    fileNameLabel->setText(fileToRead.getFileName(), dontSendNotification);

    setEnabledState(true);

    repaint();
}

void JuliaProcessorEditor::buttonEvent(Button* button)
{

    if (!acquisitionIsActive)
    {

        if (button == fileButton)
        {
            //std::cout << "Button clicked." << std::endl;
            FileChooser chooseJuliaProcessorFile("Please select the file you want to load...",
                                             lastFilePath,
                                             "*");

            if (chooseJuliaProcessorFile.browseForFileToOpen())
            {
                // Use the selected file
                setFile(chooseJuliaProcessorFile.getResult().getFullPathName());

                // lastFilePath = fileToRead.getParentDirectory();

                // thread->setFile(fileToRead.getFullPathName());

                // fileNameLabel->setText(fileToRead.getFileName(),false);
            }
        } 
        if (button == reloadFileButton)
        {
			juliaProcessor->reloadFile();
        }

    }
}

void JuliaProcessorEditor::saveEditorParameters(XmlElement* xml)
{

    // XmlElement* fileName = xml->createNewChildElement("FILENAME");
    // fileName->addTextElement(lastFilePath.getFullPathName());

}

void JuliaProcessorEditor::loadEditorParameters(XmlElement* xml)
{

    // forEachXmlChildElement(*xml, xmlNode)
    //    {
    //       if (xmlNode->hasTagName("FILENAME"))
    //       {

    //           lastFilePath = File(xmlNode->getText());
    //           thread->setFile(lastFilePath.getFullPathName());
    //           fileNameLabel->setText(lastFilePath.getFullPathName(),false);
    //       }
    //   }

}